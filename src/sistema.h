#pragma once

#include <vector>

#include "vector.h"
#include "grafo.h"

namespace sistema
{
    class Particula;

    class Sistema
    {
    private:
        grafo::Grafo m_grafo;

    public:
        Sistema(std::vector<Particula *> &particulas);

        void expandir_fuerzas();
    };

    class Particula : public grafo::Node
    {
    public:
        Vector2 m_acumulador_por_nivel;
        Vector2 m_acumulador_total;

    public:
        Particula(Vector2 fuerza);
    };

    class Interaccion : public grafo::Interaccion
    {
    private:
        Vector2 m_direccion;

    public:
        Interaccion(Vector2 direccion);

        bool valido(Particula *particula);
    };
}