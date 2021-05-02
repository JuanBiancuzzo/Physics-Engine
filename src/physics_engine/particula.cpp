#include "particula.h"

Particula::Particula(const Vector2 &pos, float masa, Area *estructura)
    : c_pos(pos), c_vel(Vector2()), c_fuerza(Vector2()), c_masa(masa), c_index(0), c_padre(nullptr), c_estructura(estructura)
{
}

void Particula::actualizar(const float dt)
{
    c_vel += c_fuerza / c_masa * dt;
    c_pos += c_vel * dt;
}
