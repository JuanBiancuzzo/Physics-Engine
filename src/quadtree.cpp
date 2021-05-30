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

bool QuadTree::actualizar(Entidad *entidad)
{
    bool resultado = false;
    for (auto &padre : entidad->m_padres)
        if (padre.first->hay_entidad(entidad))
            resultado = resultado || m_raiz->actualizar(entidad);
    return resultado;
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
        entidad->m_padres.emplace_back(std::make_pair(this, m_cant_entidades));
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
    if (m_entidades.empty())
    {
        for (Node *subdivision : m_subdivisiones)
            subdivision->eliminar(entidad);
        juntar();
    }
    else
    {
        for (auto it = entidad->m_padres.begin(); it != entidad->m_padres.end(); it++)
        {
            if (it->first == this)
            {
                m_entidades[it->second] = m_entidades[m_cant_entidades];
                entidad->m_padres.erase(it);
                break;
            }
        }
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

bool Node::hay_entidad(Entidad *entidad)
{
    for (int i = 0; i < m_cant_entidades; i++)
        if (m_entidades[i] == entidad)
            return true;
    return false;
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
        for (auto it = entidad->m_padres.begin(); it != entidad->m_padres.end(); it++)
            if (it->first == this)
            {
                entidad->m_padres.erase(it);
                break;
            }
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

    for (int i = 0; i < output.size(); i++)
    {
        m_entidades[i] = output[i];
        m_entidades[i]->m_padres.emplace_back(std::make_pair(this, i));
    }

    for (Node *subdivision : m_subdivisiones)
        for (Entidad *entidad : output)
            subdivision->eliminar(entidad);

    for (Node *subdivision : m_subdivisiones)
        subdivision->~Node();
    m_subdivisiones.clear();
}

Entidad::Entidad(CuerpoRigido *cuerpo)
    : m_cuerpo(cuerpo)
{
    m_padres.reserve(1);
}
