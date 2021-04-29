#include "particula.h"

#include <math.h>

Particula::Particula()
    : c_masa(1.0f), c_radio(1.0f), c_vel(Vector2()), c_acc(Vector2()), Entidad()
{
}

Particula::Particula(const Vector2 &pos)
    : c_masa(1.0f), c_radio(1.0f), c_vel(Vector2()), c_acc(Vector2()), Entidad(pos)
{
}

Particula::Particula(const Vector2 &pos, float masa)
    : c_masa(masa), c_radio(1.0f), c_vel(Vector2()), c_acc(Vector2()), Entidad(pos)
{
}

Particula::Particula(const Vector2 &pos, float masa, float radio)
    : c_masa(masa), c_radio(radio), c_vel(Vector2()), c_acc(Vector2()), Entidad(pos)
{
}

void Particula::aplicar_fuerza(const Vector2 &fuerza)
{
    c_acc += fuerza / c_masa;
}

void Particula::actualizar(float delta_t)
{
    c_vel += c_acc * delta_t;
    c_pos += c_vel * delta_t;

    // las fuerzas no son acumulativas
    c_acc *= .0f;
}

bool Particula::colisiona(const Particula &otro) const
{
    return (c_pos.distancia_cuadrada(otro.c_pos) <= pow(this->c_radio + otro.c_radio, 2));
}
