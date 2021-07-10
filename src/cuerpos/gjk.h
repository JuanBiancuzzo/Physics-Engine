#pragma once

#include <vector>
#include "cuerpoRigido.h"
#include "AABB.h"
#include "circulo.h"
#include "linea.h"

class Gjk
{
private:
    CuerpoRigido *m_cuerpo1;
    CuerpoRigido *m_cuerpo2;

public:
    Gjk(CuerpoRigido *cuerpo1, CuerpoRigido *cuerpo2);

    bool colisionan();

private:
    Vector2 soporte(Vector2 &dir);
};

class Simplex
{
private:
    std::vector<Vector2> m_vertices;

public:
    Simplex(Vector2 primer_vertice);

    void agregar_vertice(Vector2 &vertice);
    bool contiene_origen(Vector2 &dir);

private:
    bool caso_linea(Vector2 &dir);
    bool caso_triangulo(Vector2 &dir);
};
