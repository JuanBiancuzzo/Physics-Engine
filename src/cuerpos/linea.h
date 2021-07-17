#pragma once

#include "cuerpoRigido.h"

namespace cr
{
    class Linea : public CuerpoRigido
    {
    public:
        Vector2 m_final;

    public:
        Linea(Vector2 principio, Vector2 final);

        Vector2 punto_soporte(Vector2 dir);
    };
}