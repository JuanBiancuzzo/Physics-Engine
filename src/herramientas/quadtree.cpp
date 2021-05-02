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

bool QuadTree::insertar(Particula *particula)
{
    if (!c_area.contiene(*particula))
        return false;
    c_raiz->insertar(particula);
    return true;
}

bool QuadTree::actualizar(Particula *particula)
{
    if (!c_area.contiene(*particula))
        return false;
    Node *hoja_nueva = c_raiz->buscar_hoja(particula);

    if (hoja_nueva != particula->c_padre)
        c_raiz->actualizar(particula);
    return true;
}

void QuadTree::eliminar(Particula *particula)
{
    if (c_area.contiene(*particula))
        c_raiz->eliminar(particula);
}

void QuadTree::buscar(const Area *frontera, std::vector<Particula *> &output)
{
    if (c_area.intersecta(*frontera))
        c_raiz->buscar(frontera, output);
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
    : c_area(nueva_area), c_cant_particulas(0), c_dividido(false)
{
}

Node::~Node()
{
    if (c_dividido)
        for (Node *node : c_subdivisiones)
            delete node;
}

Node *Node::buscar_hoja(const Particula *particula)
{
    if (c_dividido)
    {
        int index = calcular_index(particula);
        return (c_subdivisiones[index])->buscar_hoja(particula);
    }
    return this;
}

/* _________
 * |_0_|_1_| -> esta es la forma en la que se van a organizar
 * |_2_|_3_|
 */
int Node::calcular_index(const Particula *particula) const
{
    Vector2 delta = particula->c_pos - c_area.c_pos;

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
    for (int i = 0; i < c_cant_particulas; i++)
    {
        int index = calcular_index(c_particulas[i]);
        c_subdivisiones[index]->insertar(c_particulas[i]);
    }
    c_dividido = true;
}

void Node::insertar(Particula *particula)
{
    if (c_cant_particulas >= capacidad_particulas)
    {
        int index = calcular_index(particula);
        if (!c_dividido)
            subdividir();
        c_subdivisiones[index]->insertar(particula);
    }
    else
    {
        particula->c_index = c_cant_particulas;
        particula->c_padre = this;
        c_particulas[c_cant_particulas] = particula;
    }
    c_cant_particulas++;
}

void Node::actualizar(Particula *particula)
{
    Particula entidad_vieja = *particula;
    entidad_vieja.c_pos = ((Node *)particula->c_padre)->c_area.c_pos;
    eliminar(&entidad_vieja);
    insertar(particula);
}

void Node::juntar()
{
    if (c_cant_particulas >= capacidad_particulas)
        return;

    std::vector<Particula *> particulas_esparcidas;
    buscar(&c_area, particulas_esparcidas);

    for (int i = 0; i < particulas_esparcidas.size(); i++)
    {
        c_particulas[i] = *(particulas_esparcidas.begin() + i);
        c_particulas[i]->c_index = i;
        c_particulas[i]->c_padre = this;
    }

    c_dividido = false;
    for (Node *node : c_subdivisiones)
        node->~Node();
}

void Node::eliminar(Particula *particula)
{
    if (c_dividido)
    {
        int index = calcular_index(particula);
        c_cant_particulas--;
        c_subdivisiones[index]->eliminar(particula);
        if (c_cant_particulas < capacidad_particulas)
            juntar();
        return;
    }

    c_particulas[particula->c_index] = c_particulas[c_cant_particulas - 1];
    c_cant_particulas--;
}

void Node::buscar(const Area *frontera, std::vector<Particula *> &output)
{
    if (!c_area.intersecta(*frontera))
        return;

    if (c_dividido)
    {
        for (Node *subdivision : c_subdivisiones)
            subdivision->buscar(frontera, output);
        return;
    }

    for (int i = 0; i < c_cant_particulas; i++)
        if (frontera->contiene(*c_particulas[i]))
            output.push_back(c_particulas[i]);
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

    for (int i = 0; i < c_cant_particulas; i++)
        if (frontera->contiene(*c_particulas[i]))
            cantidad++;
}