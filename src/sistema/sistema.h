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
        void expandir_interacciones(float dt);
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
        virtual bool actualizar() = 0;
        virtual void avanzar(float dt) = 0;
    };

    class ParticulaDinamica : public Particula
    {
    public:
        cr::InfoCuerpo *m_cuerpo;

    public:
        ParticulaDinamica(cr::InfoCuerpo *cuerpo);

        bool expandir();
        bool actualizar();
        void avanzar(float dt);
    };

    class ParticulaEstatica : public Particula
    {
        cr::CuerpoRigido *m_cuerpo;

    public:
        ParticulaEstatica(cr::CuerpoRigido *cuerpo);

        bool expandir();
        bool actualizar();
        void avanzar(float dt);
    };
}