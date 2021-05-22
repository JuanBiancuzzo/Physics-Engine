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
    if (!entidad->m_cuerpo->colisiona(&m_area).colisiono)
        return false;
    m_raiz->insertar(entidad);
    return true;
}

bool QuadTree::actualizar(Entidad *entidad)
{
    return false;
}

void QuadTree::eliminar(Entidad *entidad)
{
}

int QuadTree::cantidad(const AABB *frontera)
{
    return 0;
}

template <typename T>
void QuadTree::buscar(const AABB *frontera, std::vector<T *> &output)
{
}

Node::Node(Vector2 posicion, float ancho, float alto)
    : m_area(AABB(posicion, ancho, alto)), m_cant_particulas(0), m_dividido(false)
{
}

Node::~Node()
{
    if (m_dividido)
    {
        for (Node *subdivision : m_subdivisiones)
        {
            subdivision->~Node();
            delete subdivision;
        }
    }
}

void Node::insertar(Entidad *entidad)
{
}

void Node::actualizar(Entidad *entidad)
{
}

void Node::eliminar(Entidad *entidad)
{
}

template <typename T>
void Node::buscar(const AABB *frontera, std::vector<T *> &output)
{
}

Node *Node::buscar_hoja(const Vector2 &posicion)
{
    return nullptr;
}

void Node::subdividir()
{
    float nuevo_ancho = m_area.m_ancho / 2;
    float nuevo_ancho = m_area.m_ancho / 2;

    for (int i = 0; i < m_subdivisiones.size() / 2; i++)
    {
        for (int j = 0; j < m_subdivisiones.size() / 2; j++)
        {
            float nuevo_x = m_area.m_pos.x + nuevo_ancho * (2 * j - 1);
            float nuevo_y = m_area.m_pos.y + nuevo_ancho * (1 - 2 * i);

            int index = j + 2 * i;
            m_subdivisiones[index] = new Node(Vector2(nuevo_x, nuevo_y), nuevo_ancho, nuevo_ancho);
        }
    }
    for (Entidad *entidad : m_particulas)
        for (Node *subdivision : m_subdivisiones)
            subdivision->insertar(entidad);

    m_dividido = true;
}

void Node::juntar()
{
    std::vector<Entidad *> entidades_esparcidas;
    buscar<Entidad *>(&m_area, entidades_esparcidas);

    if (entidades_esparcidas.size() >= m_particulas.size())
        return;

    for (int i = 0; i < entidades_esparcidas.size(); i++)
    {
        m_particulas[i] = entidades_esparcidas.begin()[i];
        m_particulas[i].push_back(this);
    }

    m_dividido = false;
    for (Node *subdivision : m_subdivisiones)
        subdivision->~Node();
}

Entidad::Entidad(CuerpoRigido *cuerpo)
    : m_cuerpo(cuerpo)
{
    m_padres.reserve(1);
}
