#pragma once

#include "cuerpoRigido.h"
#include <array>

namespace cr
{

    template <int cant_vertices>
    Vector2 calcular_centro(std::array<Vector2, cant_vertices> vertices)
    {
        Vector2 centro;
        for (Vector2 vertice : vertices)
            centro += vertice;
        return centro / cant_vertices;
    }

    template <int cant_vertices>
    class Poligono : public CuerpoRigido
    {
    public:
        std::array<Vector2, cant_vertices> m_vertices;

    public:
        Poligono<cant_vertices>(Vector2 posicion, std::array<Vector2, cant_vertices> vertices)
            : CuerpoRigido(posicion), m_vertices(vertices)
        {
        }
        Poligono<cant_vertices>(std::array<Vector2, cant_vertices> vertices)
            : CuerpoRigido(calcular_centro<cant_vertices>(vertices)), m_vertices(vertices)
        {
        }

        Vector2 punto_soporte(Vector2 dir)
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

        CuerpoRigido *copia(Vector2 posicion)
        {
            std::array<Vector2, cant_vertices> vertices;
            for (int i = 0; i < cant_vertices; i++)
                vertices[i] = m_vertices[i] + posicion;
            return new Poligono<cant_vertices>(vertices);
        }
    };
}