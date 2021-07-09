#pragma once

#include "cuerpoRigido.h"
#include <vector>

class AABB : public CuerpoRigido
{
public:
    float m_ancho, m_alto;

private:
    std::vector<Vector2> m_vertices;

public:
    AABB(Vector2 posicion, float ancho, float alto);

    Vector2 punto_soporte(Vector2 dir);
};