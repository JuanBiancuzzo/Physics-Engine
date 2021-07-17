#pragma once

#include "vector.h"
#include "cuerpos/gjk.h"

#include <vector>

namespace qt
{

    class Node;
    class Entidad;

    class QuadTree
    {
    private:
        Node *m_raiz;

    public:
        QuadTree(Vector2 posicion, float ancho, float alto);
        QuadTree(cr::AABB &aabb);
        ~QuadTree();

        bool insertar(Entidad *entidad);
        void actualizar(Entidad *entidad);
        bool eliminar(Entidad *entidad);
        std::vector<Entidad *> buscar(cr::CuerpoRigido *frontera);
    };

    class Node
    {
    private:
        static const int cap_subdivisiones = 4;
        static const int cap_entidades = 4;

        cr::AABB m_area;
        std::vector<Node *> m_subdivisiones;
        std::vector<Entidad *> m_entidades;
        int m_cant_entidades;

    public:
        Node(Vector2 posicion, float ancho, float alto);
        Node(cr::AABB &aabb);
        ~Node();

        bool insertar(Entidad *entidad);
        bool eliminar(Entidad *entidad);
        void buscar(cr::CuerpoRigido *frontera, std::vector<Entidad *> &output);

        void nodos_padre(Entidad *entidad, std::vector<Node *> &padres);

    private:
        void subdividir();
        void juntar();
        bool es_divisible();

        std::vector<Node *> crear_subdivisiones();
    };

    class Entidad
    {
    public:
        std::vector<Node *> m_padres;

    public:
        Entidad();

        virtual bool colisiona(cr::CuerpoRigido *area) = 0;
    };
}