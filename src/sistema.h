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
        void expandir_fuerzas();
    };

    class Particula
    {
    public:
        Vector2 m_velocidad, m_fuerza;
        float m_masa;
        std::vector<Interaccion *> m_interacciones;

    public:
        Particula(float masa, Vector2 velocidad, Vector2 fuerza);
        Particula(float masa);
        ~Particula();

        void agregar_interaccion(Particula *referencia, Vector2 &direccion);
        void expandir();
    };

    class Particula_estatica : public Particula
    {
    public:
        Particula_estatica();

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