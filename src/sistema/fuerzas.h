#pragma once

#include "../vector.h"

namespace sistema
{
    class Intercambio
    {
    protected:
        Vector2 m_magnitud;

    public:
        Intercambio(Vector2 magnitud);

        virtual void aplicar() = 0;
    };

    class Fuerza : public Intercambio
    {
    public:
        void aplicar() override;
    };

    class Torque : public Intercambio
    {
    public:
        void aplicar() override;
    };
}