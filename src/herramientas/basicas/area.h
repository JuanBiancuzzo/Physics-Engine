#pragma once

#include "vector.h"
#include "entidad.h"

class Area
{
public:
    Vector2 c_pos;

public:
    Area(const Vector2 &pos);
    virtual bool contiene(const Entidad &entidad) const = 0;
    virtual float distancia_borde_cuadrado(const Vector2 &dir) const = 0;
    virtual bool intersecta(const Area &frontera) const = 0;
    void actualizar(Vector2 &pos);
};

class Rectangulo : public Area
{
public:
    float c_w, c_h;

public:
    Rectangulo();
    Rectangulo(const Vector2 pos);
    Rectangulo(const Vector2 pos, float w, float h);

    bool contiene(const Entidad &entidad) const;
    float distancia_borde_cuadrado(const Vector2 &dir) const;
    bool intersecta(const Area &frontera) const;
};

class Circulo : public Area
{
public:
    float c_r;

public:
    Circulo();
    Circulo(const Vector2 pos);
    Circulo(const Vector2 pos, float r);

    bool contiene(const Entidad &entidad) const;
    float distancia_borde_cuadrado(const Vector2 &dir) const;
    bool intersecta(const Area &frontera) const;
};
