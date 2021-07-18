#pragma once

#include "../vector.h"

namespace cr
{
    struct PuntoDeColision
    {
        Vector2 A, B;
        Vector2 normal;
        float distancia;
        bool colisiono;
    };

    class CuerpoRigido
    {
    public:
        Vector2 m_posicion;
        float m_rotacion; // medida en radianes
        float m_masa, m_inercia;

    public:
        CuerpoRigido(float masa, Vector2 posicion, float rotacion);
        CuerpoRigido(Vector2 posicion);

        virtual Vector2 punto_soporte(Vector2 dir) = 0;
        virtual CuerpoRigido *copia(Vector2 posicion) = 0;

        virtual float calcular_inercia();
        virtual void modificar_posicion(Vector2 valor);
        virtual void modificar_rotacion(float valor);

        PuntoDeColision punto_de_colision(CuerpoRigido *cuerpo_rigido);
        bool colisiona(CuerpoRigido *cuerpo_rigido);
    };
}