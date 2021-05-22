#pragma once

#include "vector.h"
#include "cuerpos/cuerpos.h"

#include <vector>
#include <array>

class Node;
class Entidad;

class QuadTree
{
private:
    AABB m_area;
    Node *m_raiz;

public:
    QuadTree(Vector2 posicion, float ancho, float alto);
    ~QuadTree();

    bool insertar(Entidad *entidad);
    bool actualizar(Entidad *entidad);
    void eliminar(Entidad *entidad);
    int cantidad(const AABB *frontera);
    template <typename T>
    void buscar(const AABB *frontera, std::vector<T *> &output);
};

class Node
{
private:
    static const int cant_subdivisiones = 4;
    static const int cant_particulas = 4;

    AABB m_area;
    std::array<Node *, cant_subdivisiones> m_subdivisiones;
    std::array<Entidad *, cant_particulas> m_particulas;
    bool m_dividido;

public:
    Node(Vector2 posicion, float ancho, float alto);
    ~Node();

    void insertar(Entidad *entidad);
    void actualizar(Entidad *entidad);
    void eliminar(Entidad *entidad);
    void cantidad(const AABB *frontera, int &cantidad);
    template <typename T>
    void buscar(const AABB *frontera, std::vector<T *> &output);

    Node *buscar_hoja(const Vector2 &posicion);

private:
    void subdividir();
    void juntar();
};

class Entidad
{
public:
    CuerpoRigido *m_cuerpo;
    std::vector<Node *> m_padres;

public:
    Entidad(CuerpoRigido *cuerpo);
};
