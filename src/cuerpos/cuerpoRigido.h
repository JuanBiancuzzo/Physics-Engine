#pragma once

#include "../vector.h"

namespace cr
{
    class Circulo;
    class Linea;
    class AABB;

    struct PuntoDeColision
    {
        Vector2 normal;
        float distancia;
        bool colisiono;
    };

    class CuerpoRigido
    {
    public:
        Vector2 m_posicion;

    public:
        CuerpoRigido(Vector2 posicion);

        virtual Vector2 punto_soporte(Vector2 dir) = 0;
        PuntoDeColision colisiona(CuerpoRigido *cuerpo_rigido);
    };
}