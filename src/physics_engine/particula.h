#pragma once

#include "../herramientas/vector.h"
#include "../herramientas/area.h"
#include "../herramientas/entidad.h"

class Particula : public Entidad
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

public:
    virtual Vector2 posicion() { return c_pos; }
    virtual void cambiar_posicion(Vector2 &posicion) { c_pos = posicion; }
    virtual int index() { return c_index; }
    virtual void cambiar_index(int index) { c_index = index; }
    virtual void *padre() { return c_padre; }
    virtual void cambiar_padre(void *padre) { c_padre = padre; }
};
