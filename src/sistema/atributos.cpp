#include "atributos.h"

using namespace sistema;

Fuerza::Fuerza(Vector2 magnitud = Vector2())
    : m_magnitud(magnitud)
{
}

void Fuerza::interactuar(Particula *referencia, Interaccion interaccion)
{
}

void Fuerza::avanzar(Particula *referencia)
{
}

Velocidad::Velocidad(Vector2 magnitud = Vector2())
    : m_magnitud(magnitud)
{
}

void Velocidad::interactuar(Particula *referencia, Interaccion interaccion)
{
}

Torque::Torque(float magnitud = .0f)
    : m_magnitud(magnitud)
{
}

void Torque::avanzar(Particula *referencia)
{
}

VelocidadAngular::VelocidadAngular(float magnitud = .0f)
    : m_magnitud(magnitud)
{
}

void VelocidadAngular::interactuar(Particula *referencia, Interaccion interaccion)
{
}