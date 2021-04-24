
#include "headers/node.h"

Node::Node(const Rectangulo &nueva_area)
    : c_area(nueva_area), c_dividido(false), c_cant_particulas(0)
{
}

Node::~Node()
{
    if (c_dividido)
        for (Node *node : c_subdivisiones)
            delete node;
}

Node *Node::buscar_hoja(const Particula &particula)
{
    if (c_area.contiene(particula))
    {
        if (c_dividido)
        {
            int index = calcular_index(particula);
            return (c_subdivisiones[index])->buscar_hoja(particula);
        }
        return this;
    }
    return nullptr;
}

int Node::calcular_index(const Particula &particula) const
{
    Vector2 delta = particula.c_pos - c_area.c_pos;

    int index_x = (!delta.x) ? 0 : static_cast<int>((1 + delta.x / abs(delta.x)) / 2);
    int index_y = (!delta.y) ? 0 : static_cast<int>((1 - delta.y / abs(delta.y)) / 2);

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
    for (int i = 0; i < c_cant_particulas; i++)
    {
        int index = this->calcular_index(*(c_particulas[i]));
        this->c_subdivisiones[index]->insertar(c_particulas[i]);
    }
    c_dividido = true;
}

void Node::insertar(Particula *particula)
{

    int index = calcular_index(*particula);
    if (c_cant_particulas >= capacidad_particulas)
    {
        if (!c_dividido)
            subdividir();
        c_subdivisiones[index]->insertar(particula);
        c_cant_particulas++;
    }
    else
    {
        particula->c_index = c_cant_particulas;
        particula->c_padre = this;
        c_particulas[c_cant_particulas] = particula;
        c_cant_particulas++;
    }
}

void Node::actualizar(Particula &particula)
{
    eliminar(particula);
    insertar(&particula);
}

void Node::juntar() 
{ 
    if (c_cant_particulas >= capacidad_particulas)
        return;
    int cantidad = 0;
    buscar(c_area, c_particulas, cantidad);

    for (int i = 0; i < cantidad; i++)
    {
        c_particulas[i]->c_index = i;
        c_particulas[i]->c_padre = this;
    }

    c_dividido = false;
    for (Node *node : c_subdivisiones)
        node->~Node();
}

Particula *Node::eliminar(Particula &particula)
{
    if (!c_dividido)
    {
        Particula *eliminada = c_particulas[particula.c_index];
        c_particulas[particula.c_index] = c_particulas[c_cant_particulas - 1];
        c_cant_particulas--;
        return eliminada;
    }
  
    int index = calcular_index(particula);
    c_cant_particulas--;
    Particula *eliminada = c_subdivisiones[index]->eliminar(particula);
    if (c_cant_particulas < capacidad_particulas)
        juntar();

    return eliminada;
}

void Node::buscar(const Rectangulo &frontera, Particula *output[], int &cantidad)
{
    if (!c_area.intersecta(frontera))
        return;

    if (c_dividido)
    {
        for (int i = 0; i < capacidad_sub; i++)
            c_subdivisiones[i]->buscar(frontera, output, cantidad);
    }
    else
    {
        for (int i = 0; i < c_cant_particulas; i++)
        {
            if (frontera.contiene(*c_particulas[i]))
            {
                output[cantidad] = c_particulas[i];
                cantidad++;
            }
        }
    }
}
