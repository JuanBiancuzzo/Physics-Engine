#pragma once

#include "vector.h"

class Particula
{
private:
    Vector2 c_pos, c_vel, c_acc;
    float c_masa;

public:
    Particula();
    Particula(const Vector2 &pos, float masa);

    Vector2 posicion() const;

    void aplicar_fuerza(const Vector2 &fuerza);

    void actualizar(float delta_t);
};
