#pragma once

#include "area.h"
#include "entidad.h"

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
    static const int capacidad_entidades = 4;
    static const int capacidad_sub = 4;

    Entidad *c_entidades[capacidad_entidades];
    int c_cant_entidades;

    Node *c_subdivisiones[capacidad_sub];
    bool c_dividido;

public:
    Node(const Rectangulo &nueva_area);
    ~Node();

    void insertar(Entidad *entidad);
    void actualizar(Entidad *entidad);
    void eliminar(Entidad *entidad);
    void buscar(const Area *frontera, std::vector<Entidad *> &output);
    void cantidad(const Area *frontera, int &cantidad);

    Node *buscar_hoja(const Entidad *entidad);

private:
    int calcular_index(const Entidad *entidad) const;
    void subdividir();
    void juntar();
};
