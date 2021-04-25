#pragma once

#include "vector.h"

class Entidad
{
public:
    Vector2 c_pos;
    int c_index;
    void *c_padre;

    Entidad() 
        : c_pos(Vector2()), c_index(0), c_padre(nullptr)
    {
    }
    Entidad(const Vector2 &pos) 
        : c_pos(pos), c_index(0), c_padre(nullptr) 
    {
    }
};
