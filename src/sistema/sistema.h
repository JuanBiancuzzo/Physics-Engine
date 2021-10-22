#pragma once

#include <vector>
#include "../vector.h"
#include "atributos.h"
#include "historial.h"
#include "../cuerpos/cuerpoRigido.h"

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
        void expandir_interacciones();
    };

    class Particula : public Historial<Particula *>
    {
    public: 
        Velocidad m_velocidad;
        Fuerza m_fuerza;
        VelocidadAngular m_velocidad_angular;
        Torque m_torque;

        std::vector<Interaccion> m_interacciones;

    public:
        Particula();

        void agregar_interaccion(Interaccion interaccion);

        void agregar_atributo(Velocidad velocidad);
        void agregar_atributo(Fuerza fuerza);
        void agregar_atributo(VelocidadAngular velocidad_angular);
        void agregar_atributo(Torque torque);
        
        virtual bool expandir() = 0;
        virtual void actualizar() = 0;
    };

    class ParticulaDinamica : public Particula
    {
    public:
        cr::InfoCuerpo *m_cuerpo;

    public:
        ParticulaDinamica(cr::InfoCuerpo *cuerpo);

        bool expandir();
        void actualizar();
    };

    class ParticulaEstatica : public Particula
    {
        cr::CuerpoRigido *m_cuerpo;

    public:
        ParticulaEstatica(cr::CuerpoRigido *cuerpo);

        bool expandir();
        void actualizar();
    };

    struct Interaccion
    {
        Particula *m_particula;
        Vector2 m_direccion;
    };

    // class Particula
    // {
    // public:
    //     Velocidad m_velocidad;
    //     Fuerza m_fuerza;
    //     VelocidadAngular m_velocidad_angular;
    //     Torque m_torque;

    //     float m_masa, m_coeficiente;
    //     bool m_estatica;
    //     std::vector<Interaccion *> m_interacciones;

    // private:
    //     Vector2 m_velocidad_guardada, m_fuerza_guardada;
    //     std::vector<Particula *> m_historial;

    // public:
    //     Particula(float masa, Vector2 velocidad, Vector2 fuerza, float coeficiente);
    //     Particula(); // estatica
    //     ~Particula();

    //     void agregar_interaccion(Particula *referencia, Vector2 &direccion);
    //     bool expandir();

    //     void agregar_al_historial(Particula *particula);
    //     bool visitaste(Particula *particula);

    //     void actualizar();

    //     void velocidad_por_choque(Vector2 fuerza_choque);
    //     void aplicar_fuerza(Vector2 fuerza);
    // };

    // class Interaccion
    // {
    // public:
    //     Particula *m_particula;
    //     Vector2 m_direccion;

    // public:
    //     Interaccion(Particula *particula, Vector2 &direccion);

    //     bool expandir(Particula *particula);
    // };

}