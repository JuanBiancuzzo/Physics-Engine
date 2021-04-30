#include "particula.h"

Particula::Particula()
    : c_cuerpo(), Body()
{
}

Particula::Particula(const Vector2 &pos)
    : c_cuerpo(pos), Body(pos)
{
}

Particula::Particula(const Vector2 &pos, float masa)
    : c_cuerpo(pos), Body(pos, masa)
{
}

Particula::Particula(const Vector2 &pos, float masa, float radio)
    : c_cuerpo(pos, radio), Body(pos, masa)
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
    c_cuerpo.actualizar(c_pos);

    // las fuerzas no son acumulativas
    c_acc *= .0f;
}

bool Particula::colisiona(const Particula &otro) const
{
    return c_cuerpo.intersecta(otro.c_cuerpo);
}
