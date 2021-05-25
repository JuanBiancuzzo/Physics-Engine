#pragma once

#include "vector.h"
#include "cuerpos/colisiones.h"

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
    bool eliminar(Entidad *entidad);
    template <typename T>
    std::vector<T *> buscar(CuerpoRigido *frontera);
};

class Node
{
private:
    static const int cap_subdivisiones = 4;
    static const int cap_particulas = 4;

    AABB m_area;
    std::array<Node *, cap_subdivisiones> m_subdivisiones;
    Entidad *m_particulas[cap_particulas];
    int m_cant_particulas;
    bool m_dividido;

    static int m_contador;

public:
    Node(Vector2 posicion, float ancho, float alto);
    ~Node();

    bool insertar(Entidad *entidad);
    bool actualizar(Entidad *entidad);
    bool eliminar(Entidad *entidad);
    template <typename T>
    void buscar(CuerpoRigido *frontera, std::vector<T *> &output);

    bool hay_entidad(Entidad *entidad);
    int contador();

private:
    void subdividir();
    void juntar();
};

class Entidad
{
public:
    CuerpoRigido *m_cuerpo;
    std::vector<std::pair<Node *, int>> m_padres;
    int m_contador;

public:
    Entidad(CuerpoRigido *cuerpo);
};
