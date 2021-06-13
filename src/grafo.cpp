#include "grafo.h"

using namespace grafo;

template <typename T>
bool insertar_sin_repetir(std::vector<T> &lista, T elemento)
{
    for (T e : lista)
        if (e == elemento)
            return false;
    lista.emplace_back(elemento);
    return true;
}

bool Grafo::agregar_node(Node *node)
{
    return insertar_sin_repetir<Node *>(m_nodes, node);
}

void Grafo::agregar_arista(Node *node, Node *referencia, Interaccion *interaccion)
{
    for (Node *n : m_nodes)
        if (n == node)
            node->agregar_arista(referencia, interaccion);
}

std::vector<Node *> Grafo::primeros()
{
    std::vector<Node *> lista;
    ordenar();
    for (Node *node : m_nodes)
        if (node->es_primero())
            lista.emplace_back(node);
    return lista;
}

void Grafo::expandir_interaccion(std::vector<Node *> &inicio)
{
    for (int i = 0; i < inicio.size(); i++)
    {
        for (std::pair<Node *, Interaccion *> ref : inicio[i]->m_aristas)
        {
            ref.second->expandir(inicio[i], ref.first);
            insertar_sin_repetir<Node *>(inicio, ref.first);
        }
    }
}

void Grafo::ordenar()
{
    for (Node *node : m_nodes)
        node->m_orden = invalido;

    for (Node *node : m_nodes)
        node->ordenar(m_nodes.size());
}

bool Node::agregar_arista(Node *referencia, Interaccion *interaccion)
{
    return insertar_sin_repetir<std::pair<Node *, Interaccion *>>(m_aristas, std::pair(referencia, interaccion));
}

bool Node::es_primero()
{
    return (m_orden == primero);
}

void Node::ordenar(int limite)
{
    if (m_orden < 0)
        m_orden = primero;

    for (std::pair<Node *, Interaccion *> ref : m_aristas)
    {
        if (m_orden + 1 >= limite)
            continue;
        if (m_orden >= ref.first->m_orden && ref.second->valido(this))
        {
            ref.first->m_orden = m_orden + 1;
            ref.first->ordenar(limite);
        }
    }
}