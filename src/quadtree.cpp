#include "headers/quadtree.h"

QuadTree::QuadTree(const Rectangulo &nueva_area)
    : c_area(nueva_area)
{
    c_raiz = new Node(nueva_area);
}

QuadTree::~QuadTree()
{
    delete c_raiz;
}

bool QuadTree::insertar(Particula *particula) 
{
    if (!c_area.contiene(*particula))
        return false;
    c_raiz->insertar(particula);
    return true;
}

void QuadTree::actualizar(Particula &particula)
{
    Node *hoja_nueva = c_raiz->buscar_hoja(particula);

    if (hoja_nueva != particula.c_padre)
        c_raiz->actualizar(particula);
}

Particula* QuadTree::eliminar(Particula &particula)
{
    if (c_area.contiene(particula))
        return c_raiz->eliminar(particula);
    return nullptr;
}

void QuadTree::buscar(const Rectangulo &frontera, Particula *output[], int &cantidad)
{
    cantidad = 0;
    if (c_area.intersecta(frontera))
        c_raiz->buscar(frontera, output, cantidad);
}
