#pragma once

#include "particula.h"
#include "rectangulo.h"

class Node
{
private:
    static const int capacidad_particulas = 4;
    static const int capacidad_sub = 4;

public:
    Rectangulo c_area;
    bool c_dividido;
    Particula *c_particulas[capacidad_particulas];
    int c_cant_particulas;
    Node *c_subdivisiones[capacidad_sub];

public:
    Node(const Rectangulo &nueva_area);
    ~Node();

    void insertar(Particula *particula);
    void actualizar(Particula &particula, Node *nuevo_nodo);
    Particula *eliminar(Particula &particula);
    void buscar(const Rectangulo &frontera, Particula *output[], int &cantidad);

    Node *buscar_hoja(const Particula &particula);

private:
    int calcular_index(const Particula &particula) const;
    void subdividir();
};
