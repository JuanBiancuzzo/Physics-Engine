#include "caracteristica.h"

using namespace sistema;

Caracteristica::Caracteristica()
    : m_vertices({Vector2(), Vector2()}), m_cantidad(0)
{
}

Caracteristica Caracteristica::intersecta(Caracteristica &caracteristica)
{
    Caracteristica nueva;

    if (this->m_cantidad <= 1)
    {
        nueva.agregar_vertice(this->m_vertices[0]);
    }
    else if (caracteristica.m_cantidad <= 1)
    {
        nueva.agregar_vertice(caracteristica.m_vertices[0]);
    }
    else
    {
        Vector2 centro;
        std::array<Vector2, 4> vertices = {this->m_vertices[0],
                                           this->m_vertices[1],
                                           caracteristica.m_vertices[0],
                                           caracteristica.m_vertices[1]};

        for (Vector2 vertice : vertices)
            centro += vertice / vertices.size();

        for (int i = 0; i < 4; i++)
            for (int j = i + 1; j < 4; j++)
                if (vertices[i].distancia(centro) > vertices[j].distancia(centro))
                {
                    Vector2 aux = vertices[i];
                    vertices[i] = vertices[j];
                    vertices[j] = aux;
                }
        for (int i = 0; i < 2; i++)
            nueva.agregar_vertice(vertices[i]);
    }

    return nueva;
}

void Caracteristica::agregar_vertice(Vector2 &vertice)
{
    m_vertices = {vertice, m_vertices[0]};
    m_cantidad = std::min(m_cantidad + 1, 2);
}

void Caracteristica::reemplazar_vertice(Vector2 &vertice)
{
    m_vertices = {vertice, Vector2()};
    m_cantidad = 1;
}

int Caracteristica::cantidad()
{
    return m_cantidad;
}

Vector2 Caracteristica::operator[](int i)
{
    return m_vertices[i];
}