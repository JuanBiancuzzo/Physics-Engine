#include "gtest/gtest.h"
#include "../src/grafo.h"

class Node : public grafo::Node
{
public:
    int numero;

public:
    Node() : numero(0) {}
};

class Interaccion : public grafo::Interaccion
{
public:
    bool valido(grafo::Node *node, grafo::Node *referencia) { return true; }
    void expandir(grafo::Node *node, grafo::Node *referencia)
    {
        expandir(static_cast<Node *>(node), static_cast<Node *>(referencia));
    }
    void expandir(Node *node, Node *referencia)
    {
        referencia->numero++;
    }
};

TEST(GrafoTest, Agregando_nodo_devuelve_true)
{
    grafo::Grafo grafo;
    grafo::Node node;

    ASSERT_TRUE(grafo.agregar_node(&node));
}

TEST(GrafoTest, Agregando_el_mismo_nodo_y_devuelve_false)
{
    grafo::Grafo grafo;
    grafo::Node node;

    ASSERT_TRUE(grafo.agregar_node(&node));
    ASSERT_FALSE(grafo.agregar_node(&node));
}

TEST(GrafoTest, Grafo_sin_nodos_no_tiene_primero)
{
    grafo::Grafo grafo;

    std::vector<grafo::Node *> primeros = grafo.primeros();

    ASSERT_EQ(primeros.size(), 0);
}

TEST(GrafoTest, Agregando_dos_nodos_y_una_interaccion_y_el_primero_agregado_es_primero)
{
    grafo::Grafo grafo;
    grafo::Node primer_node;
    grafo::Node segundo_node;

    Interaccion interaccion;

    grafo.agregar_node(&primer_node);
    grafo.agregar_node(&segundo_node);

    grafo.agregar_arista(&primer_node, &segundo_node, &interaccion);

    std::vector<grafo::Node *> primeros = grafo.primeros();

    ASSERT_EQ(primeros[0], &primer_node);
}

TEST(GrafoTest, Ciclo_de_tres_nodes_y_solo_hay_un_padre)
{
    grafo::Grafo grafo;
    grafo::Node node1;
    grafo::Node node2;
    grafo::Node node3;

    Interaccion interaccion;

    grafo.agregar_node(&node1);
    grafo.agregar_node(&node2);
    grafo.agregar_node(&node3);

    grafo.agregar_arista(&node1, &node2, &interaccion);
    grafo.agregar_arista(&node2, &node3, &interaccion);
    grafo.agregar_arista(&node3, &node1, &interaccion);

    std::vector<grafo::Node *> primeros = grafo.primeros();

    ASSERT_EQ(primeros.size(), 1);
}

template <typename T>
bool hay_en_lista(std::vector<T> &lista, T elemento)
{
    for (T e : lista)
        if (e == elemento)
            return true;
    return false;
}

TEST(GrafoTest, Primer_y_tercer_node_tienen_vinculo_con_el_segundo_y_el_primero_y_tercero_son_primeros)
{
    grafo::Grafo grafo;
    grafo::Node node1;
    grafo::Node node2;
    grafo::Node node3;

    Interaccion interaccion;

    grafo.agregar_node(&node1);
    grafo.agregar_node(&node2);
    grafo.agregar_node(&node3);

    grafo.agregar_arista(&node1, &node2, &interaccion);
    grafo.agregar_arista(&node3, &node2, &interaccion);

    std::vector<grafo::Node *> primeros = grafo.primeros();

    ASSERT_EQ(primeros.size(), 2);

    ASSERT_TRUE(hay_en_lista<grafo::Node *>(primeros, &node1));
    ASSERT_FALSE(hay_en_lista<grafo::Node *>(primeros, &node2));
    ASSERT_TRUE(hay_en_lista<grafo::Node *>(primeros, &node3));
}

TEST(GrafoTest, Expandir_numeros_atravez_de_tres_nodes_consecutivos)
{
    grafo::Grafo grafo;
    Node node1;
    Node node2;
    Node node3;

    grafo.agregar_node(&node1);
    grafo.agregar_node(&node2);
    grafo.agregar_node(&node3);

    Interaccion interaccion;

    grafo.agregar_arista(&node1, &node2, &interaccion);
    grafo.agregar_arista(&node2, &node3, &interaccion);

    std::vector<grafo::Node *> primeros = grafo.primeros();
    grafo.expandir_interaccion(primeros);

    ASSERT_EQ(node1.numero, 0);
    ASSERT_EQ(node2.numero, 1);
    ASSERT_EQ(node3.numero, 1);
}

TEST(GrafoTest, Expandir_numeros_en_un_ciclo_de_tres_nodo)
{
    grafo::Grafo grafo;
    Node node1;
    Node node2;
    Node node3;

    grafo.agregar_node(&node1);
    grafo.agregar_node(&node2);
    grafo.agregar_node(&node3);

    Interaccion interaccion;

    grafo.agregar_arista(&node1, &node2, &interaccion);
    grafo.agregar_arista(&node2, &node3, &interaccion);
    grafo.agregar_arista(&node3, &node1, &interaccion);

    std::vector<grafo::Node *> primeros = grafo.primeros();
    grafo.expandir_interaccion(primeros);

    ASSERT_EQ(node1.numero, 3);
    ASSERT_EQ(node2.numero, 3);
    ASSERT_EQ(node3.numero, 3);
}