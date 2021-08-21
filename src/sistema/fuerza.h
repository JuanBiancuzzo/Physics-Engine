#pragma once

#include "particula.h"

namespace sistema
{
    class Particula;

    class Fuerza
    {
    public:
        virtual ~Fuerza() = default;

        virtual bool aplicar(Vector2 direccion, Particula *particula, Particula *referencia) = 0;
        virtual void actualizar() = 0;
        virtual void modificar(Vector2 &velocidad, float &velocidad_angular, cr::InfoCuerpo *info) = 0;
    };

    class MagnitudVectorial : public Fuerza
    {
    protected:
        Vector2 m_magnitud;
        Vector2 m_magnitud_reservada;

    public:
        MagnitudVectorial(Vector2 magnitud);

        void actualizar() override;
        void reservar_magnitud(Vector2 magnitud_nueva);
    };

    class MagnitudEscalar : public Fuerza
    {
    protected:
        float m_magnitud;
        float m_magnitud_reservada;

    public:
        MagnitudEscalar(float magnitud);

        void actualizar() override;
        void reservar_magnitud(float magnitud_nueva);
    };

    class Velocidad : public MagnitudVectorial
    {
    public:
        Velocidad(Vector2 magnitud);

        bool aplicar(Vector2 direccion, Particula *particula, Particula *referencia) override;
        void modificar(Vector2 &velocidad, float &velocidad_angular, cr::InfoCuerpo *info) override;
    };

    class FuerzaAplicada : public MagnitudVectorial
    {
    public:
        FuerzaAplicada(Vector2 magnitud);

        bool aplicar(Vector2 direccion, Particula *particula, Particula *referencia) override;
        void modificar(Vector2 &velocidad, float &velocidad_angular, cr::InfoCuerpo *info) override;
        Fuerza *en_dir(Vector2 direccion);
    };

    class VelocidadAngular : public MagnitudEscalar
    {
    public:
        VelocidadAngular(float magnitud);

        bool aplicar(Vector2 direccion, Particula *particula, Particula *referencia) override;
        void modificar(Vector2 &velocidad, float &velocidad_angular, cr::InfoCuerpo *info) override;
    };

    class Torque : public MagnitudEscalar
    {
    public:
        Torque(float magnitud);

        bool aplicar(Vector2 direccion, Particula *particula, Particula *referencia) override;
        void modificar(Vector2 &velocidad, float &velocidad_angular, cr::InfoCuerpo *info) override;
    };
}