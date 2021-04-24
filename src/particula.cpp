#include "headers/particula.h"

Particula::Particula()
    : c_pos(Vector2()), c_index(0), c_padre(nullptr), c_vel(Vector2()), c_masa(1.0f), c_radio(1.0f), c_fuerza(Vector2())
{
}

Particula::Particula(const Vector2 &pos)
    : c_pos(pos), c_index(0), c_padre(nullptr), c_vel(Vector2()), c_masa(1.0f), c_radio(1.0f), c_fuerza(Vector2())
{
}

Particula::Particula(const Vector2 &pos, float masa, float radio)
    : c_pos(pos), c_index(0), c_padre(nullptr), c_vel(Vector2()), c_masa(masa), c_radio(radio), c_fuerza(Vector2())
{
}

void Particula::aplicar_fuerza(const Vector2 &fuerza) 
{
    c_fuerza += fuerza;
}

void Particula::actualizar(float delta_t) 
{
    c_vel += (c_fuerza/c_masa) * delta_t;
    c_pos += c_vel * delta_t;

    // las fuerzas no son acumulativas
    c_fuerza *= .0f;
}

bool Particula::colisiona(const Particula &otro) const
{
    return (c_pos.distancia(otro.c_pos) <= this->c_radio + otro.c_radio, 2);
}
