#pragma once

#include "area.h"
#include "entidad.h"
#include "../physics_engine/particula.h"

#include <vector>
#include <array>

class Node;

class QuadTree
{
public:
    Rectangulo c_area;

private:
    Node *c_raiz;

public:
    QuadTree(const Rectangulo &nueva_area);
    ~QuadTree();

    bool insertar(Entidad *entidad);
    bool actualizar(Entidad *entidad);
    void eliminar(Entidad *entidad);
    void buscar(const Area *frontera, std::vector<Entidad *> &output);
    int cantidad(const Area *frontera);
};

class Node
{
public:
    Rectangulo c_area;

private:
    std::array<Entidad*, 4> c_particulas;
    int c_cant_particulas;

    std::array<Nodo*, 4> c_subdivisiones;
    bool c_dividido;

public:
    Node(const Rectangulo &nueva_area);
    ~Node();

    void insertar(Entidad *entidad);
    void actualizar(Entidad *entidad);
    void eliminar(Entidad *entidad);
    void buscar(const Area *frontera, std::vector<Entidad *> &output);
    void cantidad(const Area *frontera, int &cantidad);

    Node *buscar_hoja(const Vector2 &posicion);

private:
    int calcular_index(const Vector2 &posicion) const;
    void subdividir();
    void juntar();
};
