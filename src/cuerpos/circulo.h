#pragma once

#include "cuerpoRigido.h"

class Circulo : public CuerpoRigido
{
public:
    float m_radio;

public:
    Circulo(Vector2 posicion, float radio);

    Vector2 punto_soporte(Vector2 dir);
};
