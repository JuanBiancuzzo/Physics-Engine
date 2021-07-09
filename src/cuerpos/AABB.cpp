#include "AABB.h"

AABB::AABB(Vector2 posicion, float ancho, float alto)
    : CuerpoRigido(posicion), m_ancho(ancho), m_alto(alto)
{
    m_vertices.emplace_back(Vector2(posicion.x + ancho, posicion.y + alto));
    m_vertices.emplace_back(Vector2(posicion.x - ancho, posicion.y + alto));
    m_vertices.emplace_back(Vector2(posicion.x + ancho, posicion.y - alto));
    m_vertices.emplace_back(Vector2(posicion.x - ancho, posicion.y - alto));
}

Vector2 AABB::punto_soporte(Vector2 dir)
{
    Vector2 punto_soporte = m_vertices[0];

    for (Vector2 vertice : m_vertices)
        if (vertice * dir > punto_soporte * dir)
            punto_soporte = vertice;

    return punto_soporte;
}