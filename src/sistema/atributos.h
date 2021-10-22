#pragma once
#include "sistema.h"

namespace sistema
{
    class Interactuar
    {  
    public:
        virtual void interactuar(Particula *referencia, Interaccion interaccion) = 0;
    };

    class Avanzar
    {  
    public:
        virtual void avanzar(Particula *referencia) = 0; 
    };

    class Fuerza : public Interactuar, public Avanzar
    {
    public:
        Vector2 m_magnitud;
    public:
        Fuerza(Vector2 magnitud);

        void interactuar(Particula *referencia, Interaccion interaccion);
        void avanzar(Particula *referencia);

        void operator+=(Fuerza otro);
    };

    class Velocidad : public Interactuar
    {
    public:
        Vector2 m_magnitud;
    public:
        Velocidad(Vector2 magnitud);

        void interactuar(Particula *referencia, Interaccion interaccion);

        void operator+=(Velocidad otro);
    };

    class Torque : public Avanzar
    {
    public:
        float m_magnitud;
    public:
        Torque(float magnitud);

        void avanzar(Particula *referencia);

        void operator+=(Torque otro);
    };

    class VelocidadAngular : public Interactuar
    {
    public:
        float m_magnitud;
    public:
        VelocidadAngular(float magnitud);

        void interactuar(Particula *referencia, Interaccion interaccion);

        void operator+=(VelocidadAngular otro);
    };
}