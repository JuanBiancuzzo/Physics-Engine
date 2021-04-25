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

bool QuadTree::insertar(Entidad *entidad)
{
    if (!c_area.contiene(*entidad))
        return false;
    c_raiz->insertar(entidad);
    return true;
}

bool QuadTree::actualizar(Entidad &entidad)
{
    if (!c_area.contiene(entidad))
        return false;
    Node *hoja_nueva = c_raiz->buscar_hoja(entidad);

    if (hoja_nueva != entidad.c_padre)
        c_raiz->actualizar(entidad);
    return true;
}

Entidad *QuadTree::eliminar(Entidad &entidad)
{
    if (c_area.contiene(entidad))
        return c_raiz->eliminar(entidad);
    return nullptr;
}

void QuadTree::buscar(const Rectangulo &frontera, Entidad *output[], int &cantidad)
{
    cantidad = 0;
    if (c_area.intersecta(frontera))
        c_raiz->buscar(frontera, output, cantidad);
}
