#pragma once

#include "vector.h"

class Particula
{
public:
    Vector2 c_pos, c_vel;

private:
    Vector2 c_fuerza;
    float c_masa, c_radio; 

public:
    Particula();
    Particula(const Vector2 &pos, float masa, float radio);

    void aplicar_fuerza(const Vector2 &fuerza);

    void actualizar(float delta_t);

    bool colisiona(const Particula &otro) const;
};
