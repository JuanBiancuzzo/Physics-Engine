#include "rectangulo.h"

using namespace cr;

Rectangulo::Rectangulo(float masa, Vector2 posicion, float rotacion, float ancho, float alto)
    : CuerpoRigido(masa, posicion, rotacion), m_ancho(ancho), m_alto(alto)
{
    calcular_vertices();
}

void Rectangulo::modificar_posicion(Vector2 valor)
{
    m_posicion += valor;
    for (Vector2 vertice : m_vertices)
        vertice += valor;
}

void Rectangulo::modificar_rotacion(float valor)
{
    m_rotacion += valor;
    for (Vector2 vertice : m_vertices)
        vertice = (vertice - m_posicion).rotar(valor) + m_posicion;
}

void Rectangulo::calcular_vertices()
{
    m_vertices[0] = m_posicion + (Vector2(m_ancho, .0f).rotar(m_rotacion));
    m_vertices[1] = m_posicion + (Vector2(-m_ancho, .0f).rotar(m_rotacion));
    m_vertices[2] = m_posicion + (Vector2(.0f, m_alto).rotar(m_rotacion));
    m_vertices[3] = m_posicion + (Vector2(.0f, -m_alto).rotar(m_rotacion));
}

Vector2 Rectangulo::punto_soporte(Vector2 dir)
{
    Vector2 punto_soporte;
    float distanciaMaxima = std::numeric_limits<float>::min();

    for (Vector2 vertice : m_vertices)
    {
        float distancia = (vertice - m_posicion) * dir;
        if (distancia > distanciaMaxima)
        {
            distanciaMaxima = distancia;
            punto_soporte = vertice;
        }
    }

    return punto_soporte;
}

CuerpoRigido *Rectangulo::copia(Vector2 posicion)
{
    return new Rectangulo(m_masa, m_posicion + posicion, m_rotacion, m_ancho, m_alto);
}

float Rectangulo::calcular_inercia()
{
    float masa_individual = m_masa / 4;
    float inercia = .0f;

    for (Vector2 vertice : m_vertices)
        inercia += masa_individual * (m_posicion - vertice).modulo_cuadrado();

    return inercia;
}