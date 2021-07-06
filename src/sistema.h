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
        float m_dt;

    public:
        Sistema(std::vector<Particula *> &particulas, float dt);

        void agregar_interaccion(Particula *particula, Particula *referencia, Vector2 &direccion);
        void expandir_fuerzas();
        void actualizar_particulas();
    };

    class Particula
    {
    public:
        Vector2 m_velocidad, m_fuerza;
        float m_masa, m_coeficiente;
        bool m_estatica;
        std::vector<Interaccion *> m_interacciones;

    private:
        Vector2 m_velocidad_guardada, m_fuerza_guardada;
        std::vector<Particula *> m_interactuando;

    public:
        Particula(float masa, Vector2 velocidad, Vector2 fuerza, float coeficiente);
        Particula(); // estatica
        ~Particula();

        void agregar_interaccion(Particula *referencia, Vector2 &direccion, float dt);
        bool expandir();

        void actualizarse();

        bool interactuaste(Particula *particula);
        void interactuas(Particula *particula);

        void actualizar(float dt);
        void velocidad_por_choque(Vector2 fuerza_choque);
        void aplicar_fuerza(Vector2 fuerza);
    };

    class Interaccion
    {
    private:
        Particula *m_particula;
        Vector2 m_direccion;
        float m_dt;

    public:
        Interaccion(Particula *particula, Vector2 &direccion, float dt);

        bool expandir(Particula *particula);
    };

}