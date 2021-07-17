#include "AABB.h"

using namespace cr;

AABB::AABB(Vector2 posicion, float ancho, float alto)
    : CuerpoRigido(posicion), m_ancho(ancho), m_alto(alto)
{
    calcular_vertices();
}

void AABB::calcular_vertices()
{
    m_vertices[0] = Vector2(m_posicion.x + m_ancho, m_posicion.y + m_alto);
    m_vertices[1] = Vector2(m_posicion.x - m_ancho, m_posicion.y + m_alto);
    m_vertices[2] = Vector2(m_posicion.x + m_ancho, m_posicion.y - m_alto);
    m_vertices[3] = Vector2(m_posicion.x - m_ancho, m_posicion.y - m_alto);
}

Vector2 AABB::punto_soporte(Vector2 direccion)
{
    calcular_vertices();

    Vector2 punto_soporte;
    float distanciaMaxima = std::numeric_limits<float>::min();

    for (Vector2 vertice : m_vertices)
    {
        float distancia = vertice * direccion;
        if (distancia > distanciaMaxima)
        {
            distanciaMaxima = distancia;
            punto_soporte = vertice;
        }
    }

    return punto_soporte;
}

CuerpoRigido *AABB::copia(Vector2 posicion)
{
    return new AABB(m_posicion + posicion, m_ancho, m_alto);
}