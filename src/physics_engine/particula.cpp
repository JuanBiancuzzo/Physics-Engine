#include "headers/particula.h"

#include <math.h>

Particula::Particula()
    : c_vel(Vector2()), c_masa(1.0f), c_radio(1.0f), c_fuerza(Vector2()), c_fuerza_interaccion(Vector2()), Entidad()
{
}

Particula::Particula(const Vector2 &pos)
    : c_vel(Vector2()), c_masa(1.0f), c_radio(1.0f), c_fuerza(Vector2()), c_fuerza_interaccion(Vector2()), Entidad(pos)
{
}

Particula::Particula(const Vector2 &pos, float masa)
    : c_vel(Vector2()), c_masa(masa), c_radio(1.0f), c_fuerza(Vector2()), c_fuerza_interaccion(Vector2()), Entidad(pos)
{
}

Particula::Particula(const Vector2 &pos, float masa, float radio)
    : c_vel(Vector2()), c_masa(masa), c_radio(radio), c_fuerza(Vector2()), c_fuerza_interaccion(Vector2()), Entidad(pos)
{
}

void Particula::aplicar_fuerza(const Vector2 &fuerza)
{
    c_fuerza += fuerza;
}

void Particula::aplicar_interaccion(const Vector2 &fuerza)
{
    c_fuerza_interaccion += fuerza;
}

void Particula::actualizar(float delta_t)
{
    c_vel += ((c_fuerza + c_fuerza_interaccion) / c_masa) * delta_t;
    c_pos += c_vel * delta_t;

    // las fuerzas no son acumulativas
    c_fuerza_interaccion *= .0f;
    c_fuerza *= .0f;
}

bool Particula::colisiona(const Particula &otro) const
{
    return (c_pos.distancia_cuadrada(otro.c_pos) <= pow(this->c_radio + otro.c_radio, 2));
}