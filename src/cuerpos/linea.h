#pragma once

#include "cuerpoRigido.h"

class Linea : public CuerpoRigido
{
public:
    Vector2 m_final;

public:
    Linea(Vector2 principio, Vector2 final);

    PuntoDeColision colisiona(CuerpoRigido *cuerpo_rigido);
    PuntoDeColision colisiona(Circulo *circulo);
    PuntoDeColision colisiona(Linea *linea);
    PuntoDeColision colisiona(AABB *aabb);
};