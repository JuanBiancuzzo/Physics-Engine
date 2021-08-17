#include "fuerzas.h"

using namespace sistema;

Intercambio::Intercambio(Vector2 magnitud)
    : m_magnitud(magnitud)
{
}

Fuerza::Fuerza(Vector2 magnitud)
    : Intercambio(magnitud)
{
}

void Fuerza::aplicar()
{
}

Torque::Torque(Vector2 magnitud)
    : Intercambio(magnitud)
{
}

void Torque::aplicar()
{
}