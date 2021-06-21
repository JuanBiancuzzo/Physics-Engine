#pragma once

#include <vector>

#include "vector.h"
#include "cuerpos/cuerpoRigido.h"
#include "grafo.h"

namespace sistema
{
    class Particula;
    class Interaccion;

    class Sistema
    {
    private:
        grafo::Grafo m_grafo;

    public:
        Sistema(std::vector<Particula *> &particulas);

        void agreagar_interaccion(Particula *particula, Particula *referencia, Interaccion *interaccion);
        void expandir_fuerzas();
    };

    class Particula : public grafo::Node
    {
    public:
        Vector2 m_fuerza, m_fuerza_velocidad;
        bool m_estatico;

    public:
        Particula(Vector2 &fuerza_inicial, Vector2 &fuerza_velocidad);
        Particula(bool es_estatico);
    };

    class Interaccion : public grafo::Interaccion
    {
    private:
        Vector2 m_direccion;

    public:
        Interaccion(Vector2 &direccion);

        bool valido(grafo::Node *node);
        void expandir(grafo::Node *node, grafo::Node *referencia);
    };
}