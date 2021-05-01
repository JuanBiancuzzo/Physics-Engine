#pragma once

#include "../herramientas/entidad.h"
#include "../herramientas/vector.h"
#include "../herramientas/area.h"

class Particula : public Entidad
{
public:
    Vector2 c_vel, c_acc;
    const float c_masa;
    Area *c_estructura;

public:
    Particula(const Vector2 &pos, float masa, Area *estructura);

    void actualizar(const float dt);
};
