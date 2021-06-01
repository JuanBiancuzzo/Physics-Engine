#include "quadtree.h"

QuadTree::QuadTree(Vector2 posicion, float ancho, float alto)
    : m_area(AABB(posicion, ancho, alto))
{
    m_raiz = new Node(posicion, ancho, alto);
}

QuadTree::QuadTree(AABB &aabb)
    : m_area(aabb)
{
    m_raiz = new Node(aabb);
}

QuadTree::~QuadTree()
{
    delete m_raiz;
}

bool QuadTree::insertar(Entidad *entidad)
{
    return m_raiz->insertar(entidad);
}

template <typename T>
void eliminar_de_lista(std::vector<T> &lista, T elemento)
{
    for (auto it = lista.begin(); it < lista.end(); it++)
        if (*it == elemento)
            lista.erase(it);
}

template <typename T>
bool hay_en_lista(std::vector<T> &lista, T elemento)
{
    for (auto it = lista.begin(); it < lista.end(); it++)
        if (*it == elemento)
            return true;
    return false;
}

struct Padres
{
    std::vector<Node *> viejos;
    std::vector<Node *> nuevos;
};

Padres nuevos_y_viejos(Entidad *entidad, Node *raiz)
{
    std::vector<Node *> viejos;
    std::vector<Node *> nuevos;
    std::vector<Node *> padres;
    raiz->nodos_padre(entidad, padres);

    for (Node *node : entidad->m_padres)
        if (!hay_en_lista<Node *>(padres, node))
            viejos.emplace_back(node);

    for (Node *node : padres)
        if (!hay_en_lista<Node *>(entidad->m_padres, node))
            nuevos.emplace_back(node);

    return {viejos, nuevos};
}

bool QuadTree::actualizar(Entidad *entidad)
{
    Padres padres = nuevos_y_viejos(entidad, m_raiz);
    for (Node *node : padres.viejos)
        node->eliminar(entidad);
    for (Node *node : padres.nuevos)
        node->insertar(entidad);
    return true;
}

bool QuadTree::eliminar(Entidad *entidad)
{
    return m_raiz->eliminar(entidad);
}

std::vector<Entidad *> QuadTree::buscar(CuerpoRigido *frontera)
{
    std::vector<Entidad *> output;
    m_raiz->buscar(frontera, output);
    return output;
}

Node::Node(Vector2 posicion, float ancho, float alto)
    : m_area(AABB(posicion, ancho, alto)), m_cant_entidades(0), m_divisible(true)
{
}

Node::Node(AABB &aabb)
    : m_area(aabb), m_cant_entidades(0), m_divisible(true)
{
}

Node::~Node()
{
    if (!m_subdivisiones.empty())
        for (Node *subdivision : m_subdivisiones)
            delete subdivision;
}

bool Node::insertar(Entidad *entidad)
{
    if (!m_area.colisiona(entidad->m_cuerpo).colisiono)
        return false;

    if (m_cant_entidades < cap_entidades)
    {
        m_entidades.emplace_back(entidad);
        entidad->m_padres.emplace_back(this);
    }
    else
    {
        if (m_subdivisiones.empty())
            subdividir();
        for (Node *subdivision : m_subdivisiones)
            subdivision->insertar(entidad);
    }
    m_cant_entidades++;
    return true;
}

bool Node::actualizar(Entidad *entidad)
{
    return eliminar(entidad) || insertar(entidad);
}

bool Node::eliminar(Entidad *entidad)
{
    if (!m_area.colisiona(entidad->m_cuerpo).colisiono)
        return false;

    m_cant_entidades--;
    if (!m_subdivisiones.empty())
    {
        for (Node *subdivision : m_subdivisiones)
            subdivision->eliminar(entidad);
        juntar();
    }
    else
    {
        eliminar_de_lista<Node *>(entidad->m_padres, this);
        eliminar_de_lista<Entidad *>(m_entidades, entidad);
    }

    return true;
}

void agregar_entidad_sin_repetir(std::vector<Entidad *> &lista, Entidad *entidad)
{
    for (Entidad *e : lista)
        if (e == entidad)
            return;
    lista.emplace_back(entidad);
}

void Node::buscar(CuerpoRigido *frontera, std::vector<Entidad *> &output)
{
    if (!m_area.colisiona(frontera).colisiono)
        return;

    if (!m_subdivisiones.empty())
        for (Node *subdivision : m_subdivisiones)
            subdivision->buscar(frontera, output);
    else
        for (Entidad *entidad : m_entidades)
            if (frontera->colisiona(entidad->m_cuerpo).colisiono)
                agregar_entidad_sin_repetir(output, entidad);
}

void Node::nodos_padre(Entidad *entidad, std::vector<Node *> &padres)
{
    if (!m_area.colisiona(entidad->m_cuerpo).colisiono)
        return;

    if (m_subdivisiones.empty())
        padres.emplace_back(this);
    else
        for (Node *subdivision : m_subdivisiones)
            subdivision->nodos_padre(entidad, padres);
}

void Node::subdividir()
{
    float nuevo_ancho = m_area.m_ancho / 2;
    float nuevo_alto = m_area.m_alto / 2;

    for (int i = 0; i < cap_subdivisiones; i++)
    {
        float nuevo_x = m_area.m_pos.x + nuevo_ancho * (1 - 2 * (i % 2));
        float nuevo_y = m_area.m_pos.x + nuevo_alto * (1 - 2 * ((i / 2) % 2));

        Node *subdivision = new Node(Vector2(nuevo_x, nuevo_y), nuevo_ancho, nuevo_alto);
        m_subdivisiones.emplace_back(subdivision);
    }

    for (Entidad *entidad : m_entidades)
    {
        eliminar_de_lista<Node *>(entidad->m_padres, this);
        for (Node *subdivision : m_subdivisiones)
            subdivision->insertar(entidad);
    }
    m_entidades.clear();
}

void Node::juntar()
{
    if (m_cant_entidades >= cap_entidades)
        return;

    std::vector<Entidad *> output;
    buscar(&m_area, output);
    m_entidades.swap(output);

    for (Entidad *entidad : m_entidades)
    {
        for (Node *subdivision : m_subdivisiones)
            eliminar_de_lista<Node *>(entidad->m_padres, subdivision);
        entidad->m_padres.emplace_back(this);
    }

    for (Node *subdivision : m_subdivisiones)
        subdivision->~Node();
    m_subdivisiones.clear();
}

bool Node::es_divisible()
{
    return true;
}

Entidad::Entidad(CuerpoRigido *cuerpo)
    : m_cuerpo(cuerpo)
{
    m_padres.reserve(1);
}
