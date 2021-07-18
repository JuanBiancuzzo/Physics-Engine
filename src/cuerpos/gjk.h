#pragma once

#include <array>
#include <vector>

#include "cuerpoRigido.h"
#include "AABB.h"
#include "circulo.h"
#include "poligono.h"

class Simplex;

class Gjk
{
private:
    cr::CuerpoRigido *m_cuerpo1;
    cr::CuerpoRigido *m_cuerpo2;

public:
    Gjk(cr::CuerpoRigido *cuerpo1, cr::CuerpoRigido *cuerpo2);

    bool colisionan();
    bool colisionan(Simplex &simplex);
    cr::PuntoDeColision info_colision();

private:
    Vector2 soporte(Vector2 &dir);
};

class Simplex
{
private:
    std::array<Vector2, 3> m_vertices;
    int m_cantidad;

public:
    Simplex();

    void agregar_vertice(Vector2 &vertice);
    bool contiene_origen(Vector2 &dir);

    Simplex &operator=(std::initializer_list<Vector2> lista);
    std::array<Vector2, 3>::const_iterator inicio() const;
    std::array<Vector2, 3>::const_iterator fin() const;

private:
    bool caso_linea(Vector2 &dir);
    bool caso_triangulo(Vector2 &dir);
};

class Polytope
{
private:
    std::vector<Vector2> m_vertices;

public:
    Polytope(auto inicio, auto fin);

    int cantidad();
    Vector2 &operator[](int i);
    void insertar(int posicion, Vector2 &vertice);
};
