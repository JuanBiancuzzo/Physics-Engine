#include "poligono.h"

using namespace cr;

template <int cant_vertices>
Vector2 calcular_centro(std::array<Vector2, cant_vertices> vertices)
{
    Vector2 centro;
    for (Vector2 vertice : vertices)
        centro += vertice;
    return centro / cant_vertices;
}

template <int cant_vertices>
Poligono<cant_vertices>::Poligono(std::array<Vector2, cant_vertices> vertices)
    : CuerpoRigido(calcular_centro<cant_vertices>(vertices)), m_vertices(vertices)
{
}

template <int cant_vertices>
Vector2 Poligono<cant_vertices>::punto_soporte(Vector2 dir)
{
    Vector2 punto_soporte;
    float distanciaMaxima = std::numeric_limits<float>::min();

    for (Vector2 vertice : m_vertices)
    {
        float distancia = vertice * dir;
        if (distancia > distanciaMaxima)
        {
            distanciaMaxima = distancia;
            punto_soporte = vertice;
        }
    }

    return punto_soporte;
}
