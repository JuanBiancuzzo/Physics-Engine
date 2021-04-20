#include "headers/particula.h"

Particula::Particula() 
    : c_pos(Vector2()), c_vel(Vector2()), c_acc(Vector2()), c_masa(1.0f)
{
}

Particula::Particula(const Vector2 &pos, float masa)
    : c_pos(pos), c_vel(Vector2()), c_acc(Vector2()), c_masa(masa)
{
}

Vector2 Particula::posicion() const
{
    return c_pos;
}

void Particula::aplicar_fuerza(const Vector2 &fuerza) 
{
    c_acc = fuerza / c_masa;
}

void Particula::actualizar(float delta_t) 
{
    c_vel += c_acc * delta_t;
    c_pos += c_vel * delta_t;

    // la aceleracion no es acumulativa
    c_acc *= .0f;
}
