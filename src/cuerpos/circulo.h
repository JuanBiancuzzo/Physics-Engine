#pragma once

#include "cuerpoRigido.h"

namespace cr
{
    class Circulo : public CuerpoRigido
    {
    public:
        float m_radio;

    public:
        Circulo(Vector2 posicion, float radio);
        Circulo(Vector2 posicion, float rotacion, float radio);

        Vector2 punto_soporte(Vector2 dir) override;
        sistema::Caracteristica caracteristica_en_dir(Vector2 dir) override;
        CuerpoRigido *copia(Vector2 posicion) override;
        float calcular_inercia(float masa) override;
    };
}