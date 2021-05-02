#pragma once

#include "../herramientas/vector.h"
#include "../herramientas/area.h"

class Particula
{
public:
    Vector2 c_pos, c_vel, c_fuerza;
    const float c_masa;
    int c_index;
    void *c_padre;
    Area *c_estructura;

public:
    Particula(const Vector2 &pos, float masa, Area *c_estructura);

    void actualizar(const float dt);
};
