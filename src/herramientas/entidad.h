#pragma once

#include "vector.h"

class Entidad
{
public:
    virtual ~Entidad(){};
    virtual Vector2 posicion() = 0;
    virtual void cambiar_posicion(Vector2 &posicion) = 0;
    virtual int index() = 0;
    virtual void cambiar_index(int index) = 0;
    virtual void *padre() = 0;
    virtual void cambiar_padre(void *padre) = 0;
};
