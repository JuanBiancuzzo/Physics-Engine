#pragma once

#include "vector.h"
#include "cuerpos/colisiones.h"

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
    QuadTree(AABB &aabb);
    ~QuadTree();

    bool insertar(Entidad *entidad);
    bool actualizar(Entidad *entidad);
    bool eliminar(Entidad *entidad);
    std::vector<Entidad *> buscar(CuerpoRigido *frontera);
};

class Node
{
private:
    static const int cap_subdivisiones = 4;
    static const int cap_entidades = 4;

    AABB m_area;
    std::vector<Node *> m_subdivisiones;
    std::vector<Entidad *> m_entidades;
    int m_cant_entidades;
    bool m_divisible;

public:
    Node(Vector2 posicion, float ancho, float alto);
    Node(AABB &aabb);
    ~Node();

    bool insertar(Entidad *entidad);
    bool actualizar(Entidad *entidad);
    bool eliminar(Entidad *entidad);
    void buscar(CuerpoRigido *frontera, std::vector<Entidad *> &output);

    bool hay_entidad(Entidad *entidad);

private:
    void subdividir();
    void juntar();
};

class Entidad
{
public:
    CuerpoRigido *m_cuerpo;
    std::vector<std::pair<Node *, int>> m_padres;

public:
    Entidad(CuerpoRigido *cuerpo);
};
