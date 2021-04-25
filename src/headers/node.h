#pragma once

#include "entidad.h"
#include "rectangulo.h"

class Node
{
private:
    static const int capacidad_entidades = 4;
    static const int capacidad_sub = 4;

public:
    Rectangulo c_area;
    bool c_dividido;
    Entidad *c_entidades[capacidad_entidades];
    int c_cant_entidades;
    Node *c_subdivisiones[capacidad_sub];

public:
    Node(const Rectangulo &nueva_area);
    ~Node();

    void insertar(Entidad *entidad);
    void actualizar(Entidad &entidad);
    Entidad *eliminar(Entidad &entidad);
    void buscar(const Rectangulo &frontera, Entidad *output[], int &cantidad);

    Node *buscar_hoja(const Entidad &entidad);

private:
    int calcular_index(const Entidad &entidad) const;
    void subdividir();
    void juntar();
};
