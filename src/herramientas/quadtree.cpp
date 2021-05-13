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
    if (!c_area.contiene(entidad->posicion()))
        return false;
    c_raiz->insertar(entidad);
    return true;
}

bool QuadTree::actualizar(Entidad *entidad)
{
    if (!c_area.contiene(entidad->posicion()))
        return false;
    Node *hoja_nueva = c_raiz->buscar_hoja(entidad->posicion());

    if (hoja_nueva != entidad->padre())
        c_raiz->actualizar(entidad);
    return true;
}

void QuadTree::eliminar(Entidad *entidad)
{
    if (c_area.contiene(entidad->posicion()))
        c_raiz->eliminar(entidad);
}

void QuadTree::buscar(const Area *frontera, std::vector<Entidad *> &output)
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

Node *Node::buscar_hoja(const Vector2 &posicion)
{
    if (c_dividido)
    {
        int index = calcular_index(posicion);
        return (c_subdivisiones[index])->buscar_hoja(posicion);
    }
    return this;
}

/* _________
 * |_0_|_1_| -> esta es la forma en la que se van a organizar
 * |_2_|_3_|
 */
int Node::calcular_index(const Vector2 &posicion) const
{
    Vector2 delta = posicion - c_area.c_pos;

    int index_x = (delta.x == 0) ? 0 : static_cast<int>((1 + delta.x / abs((int)delta.x)) / 2);
    int index_y = (delta.y == 0) ? 0 : static_cast<int>((1 - delta.y / abs((int)delta.y)) / 2);

    return (index_x + 2 * index_y);
}

void Node::subdividir()
{
    float nuevo_w = c_area.c_w / 2;
    float nuevo_h = c_area.c_h / 2;

    for (int i = 0; i < c_subdivisiones.size() / 2; i++)
    {
        for (int j = 0; j < c_subdivisiones.size() / 2; j++)
        {
            float nuevo_x = c_area.c_pos.x + nuevo_w * (2 * j - 1);
            float nuevo_y = c_area.c_pos.y + nuevo_h * (1 - 2 * i);

            int index = j + 2 * i;
            c_subdivisiones[index] = new Node(Rectangulo(Vector2(nuevo_x, nuevo_y), nuevo_w, nuevo_h));
        }
    }
    for (int i = 0; i < c_cant_particulas; i++)
    {
        int index = calcular_index(c_particulas[i]->posicion());
        c_subdivisiones[index]->insertar(c_particulas[i]);
    }
    c_dividido = true;
}

void Node::insertar(Entidad *entidad)
{
    if (c_cant_particulas >= c_particulas.size())
    {
        int index = calcular_index(entidad->posicion());
        if (!c_dividido)
            subdividir();
        c_subdivisiones[index]->insertar(entidad);
    }
    else
    {
        entidad->cambiar_index(c_cant_particulas);
        entidad->cambiar_padre(this);
        c_particulas[c_cant_particulas] = entidad;
    }
    c_cant_particulas++;
}

void Node::actualizar(Entidad *entidad)
{
    Vector2 pos_vieja = entidad->posicion();
    entidad->cambiar_posicion(((Node *)entidad->padre())->c_area.c_pos);
    eliminar(entidad);

    entidad->cambiar_posicion(pos_vieja);
    insertar(entidad);
}

void Node::juntar()
{
    if (c_cant_particulas >= c_particulas.size())
        return;

    std::vector<Entidad *> entidades_esparcidas;
    buscar(&c_area, entidades_esparcidas);

    for (int i = 0; i < entidades_esparcidas.size(); i++)
    {
        c_particulas[i] = *(entidades_esparcidas.begin() + i);
        c_particulas[i]->cambiar_index(i);
        c_particulas[i]->cambiar_padre(this);
    }

    c_dividido = false;
    for (Node *node : c_subdivisiones)
        node->~Node();
}

void Node::eliminar(Entidad *entidad)
{
    if (c_dividido)
    {
        int index = calcular_index(entidad->posicion());
        c_cant_particulas--;
        c_subdivisiones[index]->eliminar(entidad);
        if (c_cant_particulas < c_particulas.size())
            juntar();
        return;
    }

    c_particulas[entidad->index()] = c_particulas[c_cant_particulas - 1];
    c_cant_particulas--;
}

void Node::buscar(const Area *frontera, std::vector<Entidad *> &output)
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
        if (frontera->contiene(c_particulas[i]->posicion()))
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
        if (frontera->contiene(c_particulas[i]->posicion()))
            cantidad++;
}