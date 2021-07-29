#pragma once

#include "../vector.h"
#include <array>

namespace cr
{
    class Arista;
    class Vertice;

    class Caracteristica
    {
    public:
        std::array<Vector2, 2> m_vertices;
        int m_cantidad;

    public:
        Caracteristica();

        Caracteristica intersecta(Caracteristica &caracteristica, Vector2 &centro);

        void agregar_vertice(Vector2 &vertice);
        void reemplazar_vertice(Vector2 &vertice);
    };
}