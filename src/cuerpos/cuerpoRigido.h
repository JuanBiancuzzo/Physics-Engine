#pragma once

#include "../vector2.h"

class Circulo;
class Linea;
class AABB;

struct PuntoDeColision
{
    Vector2 normal;
    float distancia;
    bool colisiono;

    PuntoDeColision invertir()
    {
        this->normal *= -1.0f;
        return *this;
    }
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
