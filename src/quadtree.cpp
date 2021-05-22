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
    return false;
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
    : m_area(AABB(posicion, ancho, alto)), m_dividido(false)
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

void Node::cantidad(const AABB *frontera, int &cantidad)
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
}

void Node::juntar()
{
}

Entidad::Entidad(CuerpoRigido *cuerpo)
    : m_cuerpo(cuerpo)
{
    m_padres.reserve(1);
}
