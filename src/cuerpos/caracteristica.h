#pragma once

#include "../vector.h"
#include <vector>

namespace cr
{
    class Arista;
    class Vertice;

    class Caracteristica
    {
    public:
        std::vector<Vector2> m_vertices;

    public:
        Caracteristica(Vector2 principal);

        Caracteristica intersecta(Caracteristica *caracteristica);

        void agregar_vertice(Vector2 vertice);
        void reemplazar_vertice(Vector2 vertice);
    };
}