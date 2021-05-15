#pragma once

#include "cuerpoRigido.h"

class Circulo : public CuerpoRigido
{
public:
    float m_radio;

public:
    Circulo();

    PuntoDeColision colisiona(Circulo *circulo);
    PuntoDeColision colisiona(Linea *linea);
};
