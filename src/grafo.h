#pragma once

#include <vector>

namespace grafo
{
    enum estado
    {
        invalido = -1,
        primero
    };

    class Node;
    class Interaccion;

    class Grafo
    {
    private:
        std::vector<Node *> m_nodes;
        int m_limite;

    public:
        Grafo();

        bool agregar_node(Node *node);
        void agregar_arista(Node *node, Node *referencia, Interaccion *interaccion);
        std::vector<Node *> primeros();
        void expandir_interaccion(std::vector<Node *> &inicio);

    private:
        void ordenar();
    };

    class Node
    {
    public:
        int m_orden;
        std::vector<std::pair<Node *, Interaccion *>> m_aristas;
        int m_limite;

    public:
        bool agregar_arista(Node *referencia, Interaccion *interaccion);
        bool es_primero();
        void inicializar();
        void ordenar(int limite);
    };

    class Interaccion
    {
    public:
        virtual bool valido(Node *node, Node *referencia) = 0;
        virtual void expandir(Node *node, Node *referencia) = 0;
    };
}