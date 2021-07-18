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

        void agregar_interaccion(Particula *particula, Particula *referencia, Vector2 &direccion);
        void agregar_interaccion(Particula *particula, Particula *referencia);
        void expandir_interacciones();
    };

    class Particula
    {
    public:
        cr::CuerpoRigido *m_cuerpo;
        Vector2 m_velocidad, m_fuerza;
        float m_velocidad_angular, m_torque;
        float m_coeficiente;
        std::vector<Interaccion *> m_interacciones;

    protected:
        Vector2 m_velocidad_guardada, m_fuerza_guardada;
        std::vector<Particula *> m_historial;

    public:
        Particula(cr::CuerpoRigido *cuerpo, Vector2 velocidad, Vector2 fuerza, float coeficiente);
        ~Particula();

        void agregar_interaccion(Particula *referencia, Vector2 &normal, Vector2 &punto_aplicacion);
        void agregar_al_historial(Particula *particula);

        bool interactua(Particula *referencia, Vector2 &normal, Vector2 &punto_aplicacion);
        bool visitaste(Particula *particula);

        virtual bool expandir();
        virtual void actualizar();

        virtual void velocidad_por_choque(Vector2 fuerza_choque);
        virtual void aplicar_fuerza(Vector2 fuerza);
    };

    class ParticulaEstatica : public Particula
    {
    public:
        ParticulaEstatica(cr::CuerpoRigido *cuerpo);

        bool expandir() override;
        void actualizar() override;

        void velocidad_por_choque(Vector2 fuerza_choque) override;
        void aplicar_fuerza(Vector2 fuerza) override;
    };

    class Interaccion
    {
    public:
        Particula *m_particula;
        Vector2 m_normal, m_punto_aplicacion;

    public:
        Interaccion(Particula *particula, Vector2 &normal, Vector2 &punto_aplicacion);

        bool expandir(Particula *particula);
    };

}