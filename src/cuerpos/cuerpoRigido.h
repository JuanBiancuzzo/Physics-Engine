#pragma once

#include "../vector.h"

class Circulo;
class Linea;

struct PuntoDeColision
{
    Vector2 A;
    Vector2 B;
    Vector2 normal;
    float distancia;
    bool colisiono;
};

class CuerpoRigido
{
public:
    Vector2 m_pos;

public:
    virtual ~CuerpoRigido();

    virtual PuntoDeColision colisiona(CuerpoRigido *cuerpo_rigido) = 0;
    virtual PuntoDeColision colisiona(Circulo *circulo) = 0;
    virtual PuntoDeColision colisiona(Linea *linea) = 0;
};
