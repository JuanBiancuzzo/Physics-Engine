#pragma once

#include "vector.h"
#include "particula.h"

class Rectangulo
{
public:
    Vector2 c_pos;
    float c_w, c_h;

public:
    Rectangulo(const Vector2 pos);
    Rectangulo(const Vector2 pos, float w, float h);

    bool contiene(const Particula &particula) const;
    bool intersecta(const Rectangulo &frontera) const;
};