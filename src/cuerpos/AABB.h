#pragma once

#include "cuerpoRigido.h"
#include <array>

namespace cr
{

    class AABB : public CuerpoRigido
    {
    public:
        float m_ancho, m_alto;

    private:
        std::array<Vector2, 4> m_vertices;

    public:
        AABB(Vector2 posicion, float ancho, float alto);

        void calcular_vertices();
        Vector2 punto_soporte(Vector2 dir);
    };
}