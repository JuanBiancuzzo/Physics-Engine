#include "AABB.h"

using namespace cr;

AABB::AABB(Vector2 posicion, float ancho, float alto)
    : CuerpoRigido(posicion), m_ancho(ancho), m_alto(alto)
{
    calcular_vertices();
}

AABB::AABB(float masa, Vector2 posicion, float ancho, float alto)
    : CuerpoRigido(masa, posicion, .0f), m_ancho(ancho), m_alto(alto)
{
    calcular_vertices();
}

void AABB::modificar_posicion(Vector2 valor)
{
    m_posicion += valor;
    for (Vector2 vertice : m_vertices)
        vertice += valor;
}

void AABB::modificar_rotacion(float valor)
{
}

void AABB::calcular_vertices()
{
    m_vertices[0] = Vector2(m_posicion.x + m_ancho, m_posicion.y - m_alto);
    m_vertices[1] = Vector2(m_posicion.x + m_ancho, m_posicion.y + m_alto);
    m_vertices[2] = Vector2(m_posicion.x - m_ancho, m_posicion.y + m_alto);
    m_vertices[3] = Vector2(m_posicion.x - m_ancho, m_posicion.y - m_alto);
}

Vector2 AABB::punto_soporte(Vector2 direccion)
{
    Vector2 punto_soporte;
    float distanciaMaxima = std::numeric_limits<float>::min();

    for (Vector2 vertice : m_vertices)
    {
        float distancia = (vertice - m_posicion) * direccion;
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

float AABB::calcular_inercia()
{
    float masa_individual = m_masa / 4;
    float inercia = .0f;

    for (Vector2 vertice : m_vertices)
        inercia += masa_individual * (m_posicion - vertice).modulo_cuadrado();

    return inercia;
}