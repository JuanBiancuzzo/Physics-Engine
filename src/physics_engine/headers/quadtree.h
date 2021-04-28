#pragma once

#include "entidad.h"
#include "rectangulo.h"
#include "node.h"

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
    bool actualizar(Entidad &entidad);
    Entidad *eliminar(Entidad &entidad);
    void buscar(const Rectangulo &frontera, Entidad *output[], int &cantidad);
    int cantidad(const Rectangulo &frontera);
};
