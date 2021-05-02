#pragma once

#include "area.h"
#include "../physics_engine/particula.h"

#include <vector>

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

    bool insertar(Particula *particula);
    bool actualizar(Particula *particula);
    void eliminar(Particula *particula);
    void buscar(const Area *frontera, std::vector<Particula *> &output);
    int cantidad(const Area *frontera);
};

class Node
{
public:
    Rectangulo c_area;

private:
    static const int capacidad_particulas = 4;
    static const int capacidad_sub = 4;

    Particula *c_particulas[capacidad_particulas];
    int c_cant_particulas;

    Node *c_subdivisiones[capacidad_sub];
    bool c_dividido;

public:
    Node(const Rectangulo &nueva_area);
    ~Node();

    void insertar(Particula *particula);
    void actualizar(Particula *particula);
    void eliminar(Particula *particula);
    void buscar(const Area *frontera, std::vector<Particula *> &output);
    void cantidad(const Area *frontera, int &cantidad);

    Node *buscar_hoja(const Particula *particula);

private:
    int calcular_index(const Particula *particula) const;
    void subdividir();
    void juntar();
};
