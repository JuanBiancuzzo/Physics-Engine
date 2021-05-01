#include "particula.h"

Particula::Particula(const Vector2 &pos, float masa, Area *estructura)
    : Entidad(pos), c_vel(Vector2()), c_acc(Vector2()), c_masa(masa), c_estructura(estructura)
{
}

void Particula::actualizar(const float dt)
{
    c_vel += c_acc * dt;
    c_estructura->c_pos += c_vel * dt;
}
