#pragma once

#include "entidad.h"

class Particula : public Entidad
{
public:
    Vector2 c_vel;
    const float c_masa, c_radio;

private:
    Vector2 c_fuerza;
    
public:
    Particula();
    Particula(const Vector2 &pos);
    Particula(const Vector2 &pos, float masa);
    Particula(const Vector2 &pos, float masa, float radio);

    void aplicar_fuerza(const Vector2 &fuerza);

    void actualizar(float delta_t);

    bool colisiona(const Particula &otro) const;
};
