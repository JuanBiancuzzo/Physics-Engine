#pragma once

#include "../herramientas/entidad.h"
#include "../herramientas/vector.h"
#include "../herramientas/area.h"

class Body : public Entidad
{
public:
    Vector2 c_vel, c_acc;
    const float c_masa;
    Area *c_estructura;

public:
    Body();
    Body(const Vector2 &pos);
    Body(const Vector2 &pos, float masa);
    Body(const Vector2 &pos, Area *estructura);
    Body(const Vector2 &pos, float masa, Area *estructura);

    void actualizar(const float dt);
};
