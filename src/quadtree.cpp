#include "quadtree.h"

QuadTree::QuadTree(Vector2 posicion, float ancho, float alto)
    : m_area(AABB(posicion, ancho, alto))
{
    m_raiz = new Node(posicion, ancho, alto);
}

QuadTree::~QuadTree()
{
    m_raiz->~Node();
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

template <typename T>
std::vector<T *> QuadTree::buscar(CuerpoRigido *frontera)
{
    std::vector<T *> output;
    m_raiz->contador();
    m_raiz->buscar(frontera, output);
    return output;
}

Node::Node(Vector2 posicion, float ancho, float alto)
    : m_area(AABB(posicion, ancho, alto)), m_cant_particulas(0), m_dividido(false)
{
}

int Node::m_contador = 0;

Node::~Node()
{
    if (m_dividido)
        for (Node *subdivision : m_subdivisiones)
        {
            subdivision->~Node();
            delete subdivision;
        }
}

bool Node::insertar(Entidad *entidad)
{
    if (!entidad->m_cuerpo->colisiona(&m_area).colisiono)
        return false;

    if (m_cant_particulas < cap_particulas)
    {
        m_particulas[m_cant_particulas] = entidad;
        entidad->m_padres.emplace_back(std::make_pair(this, cap_particulas));
    }
    else
    {
        if (!m_dividido)
            subdividir();
        for (Node *subdivision : m_subdivisiones)
            subdivision->insertar(entidad);
    }

    m_cant_particulas++;
    return true;
}

bool Node::actualizar(Entidad *entidad)
{
    return eliminar(entidad) || insertar(entidad);
}

bool Node::eliminar(Entidad *entidad)
{
    if (!entidad->m_cuerpo->colisiona(&m_area).colisiono)
        return false;

    m_cant_particulas--;
    if (m_dividido)
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
                m_particulas[it->second] = m_particulas[m_cant_particulas];
                entidad->m_padres.erase(it);
                break;
            }
        }
    }

    return true;
}

template <typename T>
void Node::buscar(CuerpoRigido *frontera, std::vector<T *> &output)
{
    if (!frontera->colisiona(&m_area).colisiono)
        return;

    if (m_dividido)
        for (Node *subdivision : m_subdivisiones)
            subdivision->buscar(frontera, output);
    else
        for (int i = 0; i < m_cant_particulas; i++)
            if (m_particulas[i]->m_contador != m_contador || frontera->colisiona(m_particulas[i]->m_cuerpo).colisiono)
            {
                output.emplace_back(m_particulas[i]);
                m_particulas[i]->m_contador = m_contador;
            }
}

bool Node::hay_entidad(Entidad *entidad)
{
    for (int i = 0; i < m_cant_particulas; i++)
        if (m_particulas[i] == entidad)
            return true;
    return false;
}

int Node::contador()
{
    m_contador++;
    return m_contador;
}

void Node::subdividir()
{
    float nuevo_ancho = m_area.m_ancho / 2;
    float nuevo_alto = m_area.m_alto / 2;

    for (int i = 0; i < m_subdivisiones.size() / 2; i++)
    {
        for (int j = 0; j < m_subdivisiones.size() / 2; j++)
        {
            float nuevo_x = m_area.m_pos.x + nuevo_ancho * (2 * j - 1);
            float nuevo_y = m_area.m_pos.y + nuevo_alto * (1 - 2 * i);

            int index = j + 2 * i;
            m_subdivisiones[index] = new Node(Vector2(nuevo_x, nuevo_y), nuevo_ancho, nuevo_alto);
        }
    }

    for (Entidad *entidad : m_particulas)
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

    m_dividido = true;
}

void Node::juntar()
{
    if (m_cant_particulas >= cap_particulas)
        return;

    contador();
    std::vector<Entidad *> output;
    buscar<Entidad>(&m_area, output);

    for (int i = 0; i < output.size(); i++)
    {
        m_particulas[i] = output[i];
        m_particulas[i]->m_padres.emplace_back(std::make_pair(this, i));
    }

    for (Node *subdivision : m_subdivisiones)
        for (Entidad *entidad : output)
            subdivision->eliminar(entidad);

    m_dividido = false;
    for (Node *subdivision : m_subdivisiones)
        subdivision->~Node();
}

Entidad::Entidad(CuerpoRigido *cuerpo)
    : m_cuerpo(cuerpo), m_contador(-1)
{
    m_padres.reserve(1);
}
