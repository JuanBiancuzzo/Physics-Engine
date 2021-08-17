#include "AABB.h"

using namespace cr;

AABB::AABB(Vector2 posicion, float ancho, float alto)
    : CuerpoRigido(posicion), m_ancho(ancho), m_alto(alto)
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

sistema::Caracteristica AABB::caracteristica_en_dir(Vector2 dir)
{
    sistema::Caracteristica caracteristica;
    float distanciaMaxima = std::numeric_limits<float>::min();

    for (Vector2 vertice : m_vertices)
    {
        float distancia = (vertice - m_posicion) * dir;
        if (distancia > distanciaMaxima + .01f)
        {
            distanciaMaxima = distancia;
            caracteristica.reemplazar_vertice(vertice);
        }
        else if (distancia > distanciaMaxima - .01f)
        {
            caracteristica.agregar_vertice(vertice);
        }
    }

    return caracteristica;
}

CuerpoRigido *AABB::copia(Vector2 posicion)
{
    return new AABB(m_posicion + posicion, m_ancho, m_alto);
}

float AABB::calcular_inercia(float masa)
{
    float masa_individual = masa / 4;
    float inercia = .0f;

    for (Vector2 vertice : m_vertices)
        inercia += masa_individual * (m_posicion - vertice).modulo_cuadrado();

    return inercia;
}