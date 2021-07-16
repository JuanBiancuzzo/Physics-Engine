#include "AABB.h"

AABB::AABB(Vector2 posicion, float ancho, float alto)
    : CuerpoRigido(posicion), m_ancho(ancho), m_alto(alto)
{
    calcular_vertices();
}

void AABB::calcular_vertices()
{
    m_vertices.emplace_back(Vector2(m_posicion.x + m_ancho, m_posicion.y + m_alto));
    m_vertices.emplace_back(Vector2(m_posicion.x - m_ancho, m_posicion.y + m_alto));
    m_vertices.emplace_back(Vector2(m_posicion.x + m_ancho, m_posicion.y - m_alto));
    m_vertices.emplace_back(Vector2(m_posicion.x - m_ancho, m_posicion.y - m_alto));
}

Vector2 AABB::punto_soporte(Vector2 dir)
{
    calcular_vertices();
    Vector2 punto_soporte = m_vertices[0];

    for (Vector2 vertice : m_vertices)
        if (vertice * dir > punto_soporte * dir)
            punto_soporte = vertice;

    return punto_soporte;
}