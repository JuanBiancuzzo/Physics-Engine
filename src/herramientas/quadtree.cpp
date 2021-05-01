#include "quadtree.h"

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

bool QuadTree::actualizar(Entidad *entidad)
{
    if (!c_area.contiene(*entidad))
        return false;
    Node *hoja_nueva = c_raiz->buscar_hoja(entidad);

    if (hoja_nueva != entidad->c_padre)
        c_raiz->actualizar(entidad);
    return true;
}

void QuadTree::eliminar(Entidad *entidad)
{
    if (c_area.contiene(*entidad))
        c_raiz->eliminar(entidad);
}

void QuadTree::buscar(const Area *frontera, Entidad *output[], int &cantidad)
{
    cantidad = 0;
    if (c_area.intersecta(*frontera))
        c_raiz->buscar(frontera, output, cantidad);
}

int QuadTree::cantidad(const Area *frontera)
{
    int cantidad = 0;
    if (c_area.intersecta(*frontera))
        c_raiz->cantidad(frontera, cantidad);
    return cantidad;
}

/* ----- Nodo ----- */

Node::Node(const Rectangulo &nueva_area)
    : c_area(nueva_area), c_cant_entidades(0), c_dividido(false)
{
}

Node::~Node()
{
    if (c_dividido)
        for (Node *node : c_subdivisiones)
            delete node;
}

Node *Node::buscar_hoja(const Entidad *entidad)
{
    if (c_dividido)
    {
        int index = calcular_index(entidad);
        return (c_subdivisiones[index])->buscar_hoja(entidad);
    }
    return this;
}

/* _________
 * |_0_|_1_| -> esta es la forma en la que se van a organizar
 * |_2_|_3_|
 */
int Node::calcular_index(const Entidad *entidad) const
{
    Vector2 delta = entidad->c_pos - c_area.c_pos;

    int index_x = (delta.x == 0) ? 0 : static_cast<int>((1 + delta.x / abs((int)delta.x)) / 2);
    int index_y = (delta.y == 0) ? 0 : static_cast<int>((1 - delta.y / abs((int)delta.y)) / 2);

    return (index_x + 2 * index_y);
}

void Node::subdividir()
{
    float nuevo_w = c_area.c_w / 2;
    float nuevo_h = c_area.c_h / 2;

    for (int i = 0; i < capacidad_sub / 2; i++)
    {
        for (int j = 0; j < capacidad_sub / 2; j++)
        {
            float nuevo_x = c_area.c_pos.x + nuevo_w * (2 * j - 1);
            float nuevo_y = c_area.c_pos.y + nuevo_h * (1 - 2 * i);

            int index = j + 2 * i;
            c_subdivisiones[index] = new Node(Rectangulo(Vector2(nuevo_x, nuevo_y), nuevo_w, nuevo_h));
        }
    }
    for (int i = 0; i < c_cant_entidades; i++)
    {
        int index = calcular_index(c_entidades[i]);
        c_subdivisiones[index]->insertar(c_entidades[i]);
    }
    c_dividido = true;
}

void Node::insertar(Entidad *entidad)
{
    if (c_cant_entidades >= capacidad_entidades)
    {
        int index = calcular_index(entidad);
        if (!c_dividido)
            subdividir();
        c_subdivisiones[index]->insertar(entidad);
    }
    else
    {
        entidad->c_index = c_cant_entidades;
        entidad->c_padre = this;
        c_entidades[c_cant_entidades] = entidad;
    }
    c_cant_entidades++;
}

void Node::actualizar(Entidad *entidad)
{
    Entidad entidad_vieja = *entidad;
    entidad_vieja.c_pos = ((Node *)entidad->c_padre)->c_area.c_pos;
    eliminar(&entidad_vieja);
    insertar(entidad);
}

void Node::juntar()
{
    if (c_cant_entidades >= capacidad_entidades)
        return;
    int cantidad = 0;
    buscar(&c_area, c_entidades, cantidad);

    for (int i = 0; i < cantidad; i++)
    {
        c_entidades[i]->c_index = i;
        c_entidades[i]->c_padre = this;
    }

    c_dividido = false;
    for (Node *node : c_subdivisiones)
        node->~Node();
}

void Node::eliminar(Entidad *entidad)
{
    if (c_dividido)
    {
        int index = calcular_index(entidad);
        c_cant_entidades--;
        c_subdivisiones[index]->eliminar(entidad);
        if (c_cant_entidades < capacidad_entidades)
            juntar();
        return;
    }

    c_entidades[entidad->c_index] = c_entidades[c_cant_entidades - 1];
    c_cant_entidades--;
}

void Node::buscar(const Area *frontera, Entidad *output[], int &cantidad)
{
    if (!c_area.intersecta(*frontera))
        return;

    if (c_dividido)
    {
        for (Node *subdivision : c_subdivisiones)
            subdivision->buscar(frontera, output, cantidad);
        return;
    }

    for (int i = 0; i < c_cant_entidades; i++)
    {
        if (frontera->contiene(*c_entidades[i]))
        {
            output[cantidad] = c_entidades[i];
            cantidad++;
        }
    }
}

void Node::cantidad(const Area *frontera, int &cantidad)
{
    if (!c_area.intersecta(*frontera))
        return;

    if (c_dividido)
    {
        for (Node *subdivision : c_subdivisiones)
            subdivision->cantidad(frontera, cantidad);
        return;
    }

    for (int i = 0; i < c_cant_entidades; i++)
        if (frontera->contiene(*c_entidades[i]))
            cantidad++;
}