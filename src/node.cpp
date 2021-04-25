
#include "headers/node.h"

Node::Node(const Rectangulo &nueva_area)
    : c_area(nueva_area), c_dividido(false), c_cant_entidades(0)
{
}

Node::~Node()
{
    if (c_dividido)
        for (Node *node : c_subdivisiones)
            delete node;
}

Node *Node::buscar_hoja(const Entidad &entidad)
{
    if (c_area.contiene(entidad))
    {
        if (c_dividido)
        {
            int index = calcular_index(entidad);
            return (c_subdivisiones[index])->buscar_hoja(entidad);
        }
        return this;
    }
    return nullptr;
}

int Node::calcular_index(const Entidad &entidad) const
{
    Vector2 delta = entidad.c_pos - c_area.c_pos;

    int index_x = (delta.x == 0) ? 0 : static_cast<int>((1 + delta.x / abs(delta.x)) / 2);
    int index_y = (delta.y == 0) ? 0 : static_cast<int>((1 - delta.y / abs(delta.y)) / 2);

    return (index_x + 2 * index_y);
}

/* _________
 * |_0_|_1_| -> esta es la forma en la que se van a organizar
 * |_2_|_3_|
 */
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
        int index = this->calcular_index(*(c_entidades[i]));
        this->c_subdivisiones[index]->insertar(c_entidades[i]);
    }
    c_dividido = true;
}

void Node::insertar(Entidad *entidad)
{
    if (c_cant_entidades >= capacidad_entidades)
    {
        int index = calcular_index(*entidad);
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

void Node::actualizar(Entidad &entidad)
{
    Entidad entidad_vieja = entidad;
    entidad_vieja.c_pos = ((Node *)entidad.c_padre)->c_area.c_pos;
    eliminar(entidad_vieja);
    insertar(&entidad);
}

void Node::juntar()
{
    if (c_cant_entidades >= capacidad_entidades)
        return;
    int cantidad = 0;
    buscar(c_area, c_entidades, cantidad);

    for (int i = 0; i < cantidad; i++)
    {
        c_entidades[i]->c_index = i;
        c_entidades[i]->c_padre = this;
    }

    c_dividido = false;
    for (Node *node : c_subdivisiones)
        node->~Node();
}

Entidad *Node::eliminar(Entidad &entidad)
{
    Entidad *eliminar;
    if (!c_dividido)
    {
        eliminar = c_entidades[entidad.c_index];
        c_entidades[entidad.c_index] = c_entidades[c_cant_entidades - 1];
        c_cant_entidades--;
    }
    else
    {
        int index = calcular_index(entidad);
        c_cant_entidades--;
        eliminar = c_subdivisiones[index]->eliminar(entidad);
        if (c_cant_entidades < capacidad_entidades)
            juntar();
    }
    return eliminar;
}

void Node::buscar(const Rectangulo &frontera, Entidad *output[], int &cantidad)
{
    if (!c_area.intersecta(frontera))
        return;

    if (c_dividido)
    {
        for (int i = 0; i < capacidad_sub; i++)
            c_subdivisiones[i]->buscar(frontera, output, cantidad);
        return;
    }

    for (int i = 0; i < c_cant_entidades; i++)
    {
        if (frontera.contiene(*c_entidades[i]))
        {
            output[cantidad] = c_entidades[i];
            cantidad++;
        }
    }
}
