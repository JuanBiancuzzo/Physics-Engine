#pragma once

#include <vector>
#include "../vector.h"
// #include "atributos.h"
#include "historial.h"
#include "../cuerpos/cuerpoRigido.h"

namespace sistema
{
    // forward declaration 
    class Particula;
    class Interaccion;
}

namespace atributo
{

    struct Interaccion
    {
        sistema::Particula *m_particula;
        Vector2 m_direccion;
    };

    class Atributo
    {
    public:
        virtual void actualizar() = 0;
    };

    class Interactuar
    {  
    public:
        virtual bool interactuar(sistema::Particula *referencia, Interaccion interaccion) = 0;
    };

    class Avanzar
    {  
    public:
        virtual void avanzar(sistema::Particula *referencia, float dt) = 0; 
    };

    class Fuerza : public Atributo, public Interactuar, public Avanzar
    {
    public:
        Vector2 m_magnitud;
    public:
        Fuerza(Vector2 magnitud);

        void actualizar();
        bool interactuar(sistema::Particula *referencia, Interaccion interaccion);
        void avanzar(sistema::Particula *referencia, float dt);

        void operator+=(Fuerza otro);
    };

    class Velocidad : public Atributo, public Interactuar
    {
    public:
        Vector2 m_magnitud;
    public:
        Velocidad(Vector2 magnitud);

        void actualizar();
        bool interactuar(sistema::Particula *referencia, Interaccion interaccion);

        void operator+=(Velocidad otro);
    };

    class Torque : public Atributo, public Avanzar
    {
    public:
        float m_magnitud;
    public:
        Torque(float magnitud);

        void actualizar();
        void avanzar(sistema::Particula *referencia, float dt);

        void operator+=(Torque otro);
    };

    class VelocidadAngular : public Atributo, public Interactuar
    {
    public:
        float m_magnitud;
    public:
        VelocidadAngular(float magnitud);

        void actualizar();
        bool interactuar(sistema::Particula *referencia, Interaccion interaccion);

        void operator+=(VelocidadAngular otro);
    };
}

namespace sistema
{
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

        void agregar_interaccion(Particula *particula, Particula *referencia, Vector2 &direccion);
        void expandir_interacciones(float dt);
    };

    class Particula : public Historial<Particula *>
    {
    public: 
        atributo::Velocidad m_velocidad;
        atributo::Fuerza m_fuerza;
        atributo::VelocidadAngular m_velocidad_angular;
        atributo::Torque m_torque;

        std::vector<atributo::Interaccion> m_interacciones;

    public:
        Particula();

        void agregar_interaccion(atributo::Interaccion interaccion);

        void agregar_atributo(atributo::Velocidad velocidad);
        void agregar_atributo(atributo::Fuerza fuerza);
        void agregar_atributo(atributo::VelocidadAngular velocidad_angular);
        void agregar_atributo(atributo::Torque torque);
        
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
        InfoCuerpo *m_cuerpo;

    public:
        ParticulaDinamica(InfoCuerpo *cuerpo);

        bool expandir();
        void actualizar();
        void avanzar(float dt);

        float masa(float segunda_opcion);
        float coeficiente(float segunda_opcion);
        bool refleja_fuerza();
    };

    class ParticulaEstatica : public Particula
    {
        cr::CuerpoRigido *m_cuerpo;

    public:
        ParticulaEstatica(cr::CuerpoRigido *cuerpo);

        bool expandir();
        void actualizar();
        void avanzar(float dt);

        float masa(float segunda_opcion);
        float coeficiente(float segunda_opcion);
        bool refleja_fuerza();
    };
}