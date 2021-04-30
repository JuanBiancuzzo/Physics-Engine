#pragma once

#include "body.h"
#include "../herramientas/basicas/area.h"

class Particula : public Body
{
public:
    Circulo c_cuerpo;

public:
    Particula();
    Particula(const Vector2 &pos);
    Particula(const Vector2 &pos, float masa);
    Particula(const Vector2 &pos, float masa, float radio);

    void aplicar_fuerza(const Vector2 &fuerza);

    void actualizar(float delta_t);
    bool colisiona(const Particula &otro) const;
};
