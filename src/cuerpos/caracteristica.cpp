#include "caracteristica.h"

using namespace cr;

Caracteristica::Caracteristica(Vector2 principal)
    : m_vertices({principal})
{
}

Caracteristica Caracteristica::intersecta(Caracteristica *caracteristica)
{
    return *this;
}

void Caracteristica::agregar_vertice(Vector2 vertice)
{
    m_vertices.emplace_back(vertice);
}

void Caracteristica::reemplazar_vertice(Vector2 vertice)
{
    m_vertices.clear();
    agregar_vertice(vertice);
}