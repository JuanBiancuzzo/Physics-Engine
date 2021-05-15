#pragma once

#include "cuerpoRigido.h"

class Circulo : public CuerpoRigido
{
public:
    float m_radio;

public:
    Circulo(Vector2 posicion, float radio);

    PuntoDeColision colisiona(CuerpoRigido *cuerpo_rigido);
    PuntoDeColision colisiona(Circulo *circulo);
    PuntoDeColision colisiona(Linea *linea);
};
