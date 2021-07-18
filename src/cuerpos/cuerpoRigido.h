#pragma once

#include "../vector.h"

namespace cr
{
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
        virtual CuerpoRigido *copia(Vector2 posicion) = 0;

        PuntoDeColision punto_de_colision(CuerpoRigido *cuerpo_rigido);
        bool colisiona(CuerpoRigido *cuerpo_rigido);
    };
}