#pragma once

#include "../vector.h"
#include <array>

namespace sistema
{
    class Caracteristica
    {
    public:
        std::array<Vector2, 2> m_vertices;
        int m_cantidad;

    public:
        Caracteristica();

        Caracteristica intersecta(Caracteristica &caracteristica);

        void agregar_vertice(Vector2 &vertice);
        void reemplazar_vertice(Vector2 &vertice);
        int cantidad();

        Vector2 operator[](int i);
    };
}