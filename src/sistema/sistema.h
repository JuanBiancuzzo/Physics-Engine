#pragma once

#include <vector>
#include "../vector.h"
#include "historial.h"
#include "../cuerpos/gjk.h"

namespace sistema
{
    // forward declaration 
    class Particula;
    class ParticulaDinamica;
    class ParticulaEstatica;

    struct Interaccion
    {
        sistema::Particula *m_particula;
        Vector2 m_direccion;

        bool operator==(Interaccion otro)
        {
            return m_particula == otro.m_particula;
        }
    };

    class Atributo
    {
    public:
        virtual void actualizar() = 0;
    };

    class Interactuar
    {  
    public:
        virtual bool interactuar(sistema::ParticulaDinamica *referencia, Interaccion interaccion) = 0;
    };

    class Avanzar
    {  
    public:
        virtual void avanzar(sistema::ParticulaDinamica *referencia, float dt) = 0; 
    };

    class Fuerza : public Atributo, public Interactuar, public Avanzar
    {
    public:
        Vector2 m_magnitud;
    public:
        Fuerza(Vector2 magnitud);

        void actualizar();
        bool interactuar(sistema::ParticulaDinamica *referencia, Interaccion interaccion);
        void avanzar(sistema::ParticulaDinamica *referencia, float dt);

        void operator+=(Fuerza otro);
    };

    class Velocidad : public Atributo, public Interactuar
    {
    public:
        Vector2 m_magnitud;
    public:
        Velocidad(Vector2 magnitud);

        void actualizar();
        bool interactuar(sistema::ParticulaDinamica *referencia, Interaccion interaccion);

        void operator+=(Velocidad otro);
    };

    class Torque : public Atributo, public Avanzar
    {
    public:
        float m_magnitud;
    public:
        Torque(float magnitud);

        void actualizar();
        void avanzar(sistema::ParticulaDinamica *referencia, float dt);

        void operator+=(Torque otro);
    };

    class VelocidadAngular : public Atributo, public Interactuar
    {
    public:
        float m_magnitud;
    public:
        VelocidadAngular(float magnitud);

        void actualizar();
        bool interactuar(sistema::ParticulaDinamica *referencia, Interaccion interaccion);

        void operator+=(VelocidadAngular otro);
    };

    struct InfoCuerpo
    {
        cr::CuerpoRigido *cuerpo;
        float masa, inercia, coeficiente;

        InfoCuerpo(cr::CuerpoRigido *_cuerpo, float _masa, float _coeficiente);
    };    

    class Sistema
    {
    private:
        std::vector<Particula *> m_particulas;

    public:
        Sistema(std::vector<Particula *> particulas);

        void agregar_interaccion(Particula *particula, ParticulaDinamica *referencia);
        void agregar_interaccion(Particula *particula, ParticulaEstatica *referencia);
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

        virtual void agregar_interaccion(ParticulaDinamica *referencia) = 0;
        virtual void agregar_interaccion(ParticulaEstatica *referencia) = 0;

        void agregar_atributo(Velocidad velocidad);
        void agregar_atributo(Fuerza fuerza);
        void agregar_atributo(VelocidadAngular velocidad_angular);
        void agregar_atributo(Torque torque);
        
        virtual bool expandir() = 0;
        virtual void actualizar() = 0;
        virtual void avanzar(float dt) = 0;

        virtual float masa(float segunda_opcion) = 0;
        virtual float coeficiente(float segunda_opcion) = 0;
        virtual bool refleja_fuerza() = 0;
    };

    class ParticulaDinamica : public Particula
    {
    public:
        InfoCuerpo m_cuerpo;

    public:
        ParticulaDinamica(InfoCuerpo cuerpo);

        void agregar_interaccion(ParticulaDinamica *referencia);
        void agregar_interaccion(ParticulaEstatica *referencia);

        bool expandir();
        void actualizar();
        void avanzar(float dt);

        float masa(float segunda_opcion);
        float coeficiente(float segunda_opcion);
        bool refleja_fuerza();

        Vector2 velocidad();
        float velocidad_angular();
    };

    class ParticulaEstatica : public Particula
    {
    public:
        cr::CuerpoRigido *m_cuerpo;

    public:
        ParticulaEstatica(cr::CuerpoRigido *cuerpo);

        void agregar_interaccion(ParticulaDinamica *referencia);
        void agregar_interaccion(ParticulaEstatica *referencia);

        bool expandir();
        void actualizar();
        void avanzar(float dt);

        float masa(float segunda_opcion);
        float coeficiente(float segunda_opcion);
        bool refleja_fuerza();
    };
}