#include "atributos.h"

using namespace sistema;

Fuerza::Fuerza(Vector2 magnitud = Vector2())
    : m_magnitud(magnitud)
{
}

bool Fuerza::interactuar(Particula *referencia, Interaccion interaccion)
{
}

void Fuerza::avanzar(Particula *referencia)
{
}

void Fuerza::operator+=(Fuerza otro)
{
    m_magnitud += otro.m_magnitud;
}

Velocidad::Velocidad(Vector2 magnitud = Vector2())
    : m_magnitud(magnitud)
{
}

bool Velocidad::interactuar(Particula *referencia, Interaccion interaccion)
{
}

void Velocidad::operator+=(Velocidad otro)
{
    m_magnitud += otro.m_magnitud;
}

Torque::Torque(float magnitud = .0f)
    : m_magnitud(magnitud)
{
}

void Torque::avanzar(Particula *referencia)
{
}

void Torque::operator+=(Torque otro)
{
    m_magnitud += otro.m_magnitud;
}

VelocidadAngular::VelocidadAngular(float magnitud = .0f)
    : m_magnitud(magnitud)
{
}

bool VelocidadAngular::interactuar(Particula *referencia, Interaccion interaccion)
{
}

void VelocidadAngular::operator+=(VelocidadAngular otro)
{
    m_magnitud += otro.m_magnitud;
}