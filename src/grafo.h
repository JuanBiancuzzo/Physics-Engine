#pragma once

#include <vector>
#include <utility>

namespace grafo
{
    enum estado {
        invalido, primero, otro
    };

    class Node;
    class Interaccion;

    class Grafo
    {
    private:
        std::vector<Node *> m_nodes;

    public:
        bool agregar_node(Node *node);
        void agregar_arista(Node *node, Node *referencia, Interaccion *interaccion);
        std::vector<Node *> primeros();

    private:
        void ordenar();
    };

    class Node
    {
    private:
        int m_orden;
        std::vector<std::pair<Node *, Interaccion *>> m_aristas;

    public:
        Node();
        bool agregar_arista(Node *referencia, Interaccion *interaccion);
        bool es_primero();
        void ordenar();
    };

    class Interaccion
    {
    public:
        virtual bool valido() = 0;
    };
}