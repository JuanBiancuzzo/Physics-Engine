#pragma once

#include <vector>

#include "vector.h"

namespace sistema
{
    class Particula;
    class Interaccion;

    class Sistema
    {
    private:
        std::vector<Particula *> m_particulas;

    public:
        Sistema(std::vector<Particula *> &particulas);

        void agregar_interaccion(Particula *particula, Particula *referencia, Vector2 &direccion);
        std::vector<Particula *> primeras_particulas();
        void expandir_fuerzas();
    };

    class Particula
    {
    public:
        Vector2 m_fuerza;
        std::vector<Interaccion *> m_interacciones;

    public:
        Particula(Vector2 &fuerza);
        ~Particula();

        void agregar_interaccion(Particula *referencia, Vector2 &direccion);
        void expandir();
    };

    class Interaccion
    {
    private:
        Particula *m_particula;
        Vector2 m_direccion;

    public:
        Interaccion(Particula *particula, Vector2 &direccion);

        Vector2 expandir(Vector2 &fuerza);
    };

}