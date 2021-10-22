#pragma once

#include "../vector.h"
#include "caracteristica.h"

namespace cr
{

    struct PuntoDeColision
    {
        sistema::Caracteristica caracteristica;
        Vector2 normal;
        bool colisiono;
    };

    class CuerpoRigido
    {
    public:
        Vector2 m_posicion;
        float m_rotacion; // medida en radianes

    public:
        CuerpoRigido(Vector2 posicion, float rotacion);
        CuerpoRigido(Vector2 posicion);

        virtual Vector2 punto_soporte(Vector2 dir) = 0;
        virtual sistema::Caracteristica caracteristica_en_dir(Vector2 dir) = 0;
        virtual CuerpoRigido *copia(Vector2 posicion) = 0;

        virtual float calcular_inercia(float masa) = 0;
        virtual void modificar_posicion(Vector2 valor);
        virtual void modificar_rotacion(float valor);

        PuntoDeColision punto_de_colision(CuerpoRigido *cuerpo_rigido);
        bool colisiona(CuerpoRigido *cuerpo_rigido);
    };

    struct InfoCuerpo
    {
        CuerpoRigido *cuerpo;
        float masa, inercia;

        InfoCuerpo(CuerpoRigido *_cuerpo, float _masa);
    };
}