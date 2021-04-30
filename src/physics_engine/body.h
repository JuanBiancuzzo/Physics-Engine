#pragma once

#include "../herramientas/basicas/entidad.h"
#include "../herramientas/basicas/vector.h"
#include "../herramientas/basicas/area.h"

class Body : public Entidad
{
public:
    Vector2 c_vel, c_acc;
    const float c_masa;

public:
    Body();
    Body(const Vector2 &pos);
    Body(const Vector2 &pos, float masa);

    void actualizar();
};
