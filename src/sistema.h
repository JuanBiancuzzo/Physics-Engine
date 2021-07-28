#pragma once

#include <vector>

#include "vector.h"
#include "cuerpos/gjk.h"

namespace sistema
{
    class Particula;
    class Interaccion;

    class Sistema
    {
    private:
        std::vector<Particula *> m_particulas;

    public:
        Sistema(std::vector<Particula *> particulas);

        void agregar_interaccion(Particula *particula, Particula *referencia);
        void expandir_interacciones();
    };

    struct Interaccion
    {
        Particula *particula;
        Vector2 normal;
    };

    class Particula
    {
    public:
        cr::CuerpoRigido *m_cuerpo;
        Vector2 m_velocidad, m_fuerza;
        float m_velocidad_angular, m_torque;
        float m_coeficiente;
        std::vector<Interaccion> m_interacciones;

    protected:
        Vector2 m_velocidad_guardada, m_fuerza_guardada;
        std::vector<Particula *> m_historial;
        bool m_es_estatico;

    public:
        Particula(cr::CuerpoRigido *cuerpo, Vector2 velocidad, Vector2 fuerza, float velocidad_angular, float torque, float coeficiente);
        Particula(cr::CuerpoRigido *cuerpo, Vector2 velocidad, Vector2 fuerza, float coeficiente);
        Particula(cr::CuerpoRigido *cuerpo);

        void agregar_interaccion(Particula *referencia);
        bool visitaste(Particula *particula);

        bool expandir();
        void actualizar();

        bool choca(Particula *particula, Vector2 &normal);
        Vector2 fuerza_de_choque(Particula *particula, Vector2 &direccion);
        Vector2 velocidad_en_direccion(Vector2 &direccion);

        void velocidad_por_choque(Vector2 fuerza_choque);
        void aplicar_fuerza(Vector2 fuerza);
    };
}