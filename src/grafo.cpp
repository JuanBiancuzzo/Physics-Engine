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
    {
        if (n == node)
        {
            agregar_node(referencia);
            node->agregar_arista(referencia, interaccion);
        }
    }
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

void Grafo::ordenar()
{
    for (Node *node : m_nodes)
        node->ordenar();
}

Node::Node()
    : m_orden(invalido)
{
}

bool Node::agregar_arista(Node *referencia, Interaccion *interaccion)
{
    return insertar_sin_repetir<std::pair<Node *, Interaccion *>>(m_aristas, std::pair(referencia, interaccion));
}

bool Node::es_primero()
{
    return (m_orden == primero);
}

void Node::ordenar()
{
    if (m_orden == otro)
        return;
    if (m_orden == invalido)
        m_orden = primero;

    for (std::pair<Node *, Interaccion *> ref : m_aristas)
    {
        if (ref.first->m_orden == otro)
            continue;
        if (ref.second->valido())
        {
            ref.first->m_orden = otro;
            ref.first->ordenar();
        }
    }
}