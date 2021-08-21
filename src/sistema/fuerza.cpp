#include "fuerza.h"

using namespace sistema;

MagnitudVectorial::MagnitudVectorial(Vector2 magnitud)
    : m_magnitud(magnitud), m_magnitud_reservada(magnitud)
{
}

void MagnitudVectorial::actualizar()
{
    m_magnitud = m_magnitud_reservada;
}

void MagnitudVectorial::reservar_magnitud(Vector2 magnitud_nueva)
{
    m_magnitud_reservada += magnitud_nueva;
}

Velocidad::Velocidad(Vector2 magnitud)
    : MagnitudVectorial(magnitud)
{
}

bool Velocidad::aplicar(Vector2 direccion, Particula *particula, Particula *referencia)
{
    if (!referencia->puede_interactuar(referencia) || m_magnitud * direccion <= 0)
        return false;

    Vector2 fuerza_choque = ((ParticulaDinamica *)particula)->fuerza_de_choque(referencia, direccion);

    if (fuerza_choque * direccion <= 0)
        return false;

    std::unique_ptr<Fuerza> fuerza(new Velocidad(fuerza_choque));
    referencia->aplicar_fuerza(fuerza);

    reservar_magnitud(fuerza_choque * -1.0f);
    return true;
}

void Velocidad::modificar(Vector2 &velocidad, float &velocidad_angular, cr::InfoCuerpo *info)
{
    velocidad += m_magnitud;
}

FuerzaAplicada::FuerzaAplicada(Vector2 magnitud)
    : MagnitudVectorial(magnitud)
{
}

bool FuerzaAplicada::aplicar(Vector2 direccion, Particula *particula, Particula *referencia)
{
    if (!referencia->puede_interactuar(referencia) || m_magnitud * direccion <= 0)
        return false;

    Vector2 fuerza_direccionada = m_magnitud.proyeccion(direccion);
    std::unique_ptr<Fuerza> fuerza(new FuerzaAplicada(fuerza_direccionada));
    referencia->aplicar_fuerza(fuerza);

    reservar_magnitud(fuerza_direccionada * -1.0f);
    return true;
}

void FuerzaAplicada::modificar(Vector2 &velocidad, float &velocidad_angular, cr::InfoCuerpo *info)
{
    if (info->masa > 0)
        velocidad += m_magnitud / info->masa;
}

Fuerza *FuerzaAplicada::en_dir(Vector2 direccion)
{
    m_magnitud = m_magnitud.proyeccion(direccion);
    return this;
}

MagnitudEscalar::MagnitudEscalar(float magnitud)
    : m_magnitud(magnitud), m_magnitud_reservada(magnitud)
{
}

void MagnitudEscalar::actualizar()
{
    m_magnitud = m_magnitud_reservada;
}

void MagnitudEscalar::reservar_magnitud(float magnitud_nueva)
{
    m_magnitud_reservada += magnitud_nueva;
}

VelocidadAngular::VelocidadAngular(float magnitud)
    : MagnitudEscalar(magnitud)
{
}

bool VelocidadAngular::aplicar(Vector2 direccion, Particula *particula, Particula *referencia)
{
    return true;
}

void VelocidadAngular::modificar(Vector2 &velocidad, float &velocidad_angular, cr::InfoCuerpo *info)
{
}

Torque::Torque(float magnitud)
    : MagnitudEscalar(magnitud)
{
}

bool Torque::aplicar(Vector2 direccion, Particula *particula, Particula *referencia)
{
    return true;
}

void Torque::modificar(Vector2 &velocidad, float &velocidad_angular, cr::InfoCuerpo *info)
{
}