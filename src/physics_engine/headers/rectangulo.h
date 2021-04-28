#pragma once

#include "vector.h"
#include "entidad.h"

class Rectangulo
{
public:
    Vector2 c_pos;
    float c_w, c_h;

public:
    Rectangulo();
    Rectangulo(const Vector2 pos);
    Rectangulo(const Vector2 pos, float w, float h);

    bool contiene(const Entidad &entidad) const;
    bool intersecta(const Rectangulo &frontera) const;
};