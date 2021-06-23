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
        std::vector<Interaccion *> m_interacciones;
        float m_dt;

    public:
        Sistema(float dt);
        ~Sistema();

        void agregar_particula(Particula *particula);
        void agregar_interaccion(Particula *particula, Particula *referencia, Vector2 direccion);
        void expandir_fuerzas();
    };

    class Particula : public grafo::Node
    {
    public:
        float m_masa;
        Vector2 m_velocidad, m_fuerza;
        bool m_estatico;

    public:
        Particula(float masa, Vector2 &velocidad, Vector2 &fuerza);
        Particula(bool es_estatico);

        Vector2 fuerza_final();
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