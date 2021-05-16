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

Entidad::Entidad(CuerpoRigido *cuerpo)
    : m_cuerpo(cuerpo)
{
    m_padres.reserve(1);
}
