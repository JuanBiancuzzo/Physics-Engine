#pragma once

#include "cuerpoRigido.h"
#include <array>

namespace cr
{
    template <int cant_vertices>
    class Poligono : public CuerpoRigido
    {
    public:
        std::array<Vector2, cant_vertices> m_vertices;

    public:
        Poligono<cant_vertices>(Vector2 posicion, std::array<Vector2, cant_vertices> vertices);
        Poligono<cant_vertices>(std::array<Vector2, cant_vertices> vertices);

        Vector2 punto_soporte(Vector2 dir);
        CuerpoRigido *copia(Vector2 posicion);
    };
}