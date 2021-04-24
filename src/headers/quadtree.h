#pragma once

#include "particula.h"
#include "rectangulo.h"
#include "node.h"

class QuadTree
{
public:
    Rectangulo c_area;

private:
    Node* c_raiz;

public:
    QuadTree(const Rectangulo& nueva_area);
    ~QuadTree();

    bool insertar(Particula *particula);
    void actualizar(Particula &particula);
    Particula* eliminar(Particula &particula);
    void buscar(const Rectangulo &frontera, Particula *output[], int &cantidad);
};
