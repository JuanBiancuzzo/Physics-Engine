#pragma once

#include "vector.h"
#include "cuerpos/cuerpos.h"

#include <vector>
#include <array>

class Node;
class Entidad;

class QuadTree
{
private:
    AABB m_area;
    Node *m_raiz;

public:
    QuadTree(Vector2 posicion, float ancho, float alto);
    ~QuadTree();
};

class Node
{
private:
    static const int cant_subdivisiones = 4;
    static const int cant_particulas = 4;

    AABB m_area;
    std::array<Node *, cant_subdivisiones> m_subdivisiones;
    std::array<Entidad *, cant_particulas> m_particulas;
    bool m_dividido;

public:
    Node(Vector2 posicion, float ancho, float alto);
    ~Node();
};

class Entidad
{
public:
    CuerpoRigido *m_cuerpo;
    std::vector<Node *> m_padres;

public:
    Entidad(CuerpoRigido *cuerpo);
};
