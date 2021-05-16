#pragma once

#include "../vector.h"

class Circulo;
class Linea;
class AABB;

struct PuntoDeColision
{
    Vector2 A;
    Vector2 B;
    Vector2 normal;
    float distancia;
    bool colisiono;

    void invertir()
    {
        Vector2 temp = this.B;
        this.B = this.A;
        this.A = temp;
        this.normal *= -1.0f;
    }
};

class CuerpoRigido
{
public:
    Vector2 m_pos;

public:
    CuerpoRigido(Vector2 posicion) : m_pos(posicion) {}

    virtual PuntoDeColision colisiona(CuerpoRigido *cuerpo_rigido) = 0;
    virtual PuntoDeColision colisiona(Circulo *circulo) = 0;
    virtual PuntoDeColision colisiona(Linea *linea) = 0;
    virtual PuntoDeColision colisiona(AABB *aabb) = 0;
};
