#include "particula.h"

using namespace sistema;

Particula::Particula(cr::CuerpoRigido *cuerpo)
    : m_cuerpo(cuerpo)
{
}

void Particula::aplicar_fuerza(std::shared_ptr<Fuerza> &fuerza)
{
    m_fuerzas.emplace_back(fuerza);
}

void Particula::agregar_interaccion(Particula *referencia)
{
    for (Interaccion interaccion : m_interacciones)
        if (interaccion.particula == referencia)
            return;

    cr::PuntoDeColision pdc = m_cuerpo->punto_de_colision(referencia->m_cuerpo);
    Interaccion interaccion = {referencia, pdc.normal, pdc.caracteristica};

    m_interacciones.emplace_back(interaccion);
}

ParticulaDinamica::ParticulaDinamica(cr::InfoCuerpo *info, Vector2 velocidad, float velocidad_angular, float coeficiente)
    : Particula(info->cuerpo), m_info(info), m_coeficiente(coeficiente)
{
    std::shared_ptr<Fuerza> velocidad_cuerpo(new Velocidad(velocidad));
    aplicar_fuerza(velocidad_cuerpo);
    std::shared_ptr<Fuerza> velocidad_angular_cuerpo(new VelocidadAngular(velocidad_angular));
    aplicar_fuerza(velocidad_angular_cuerpo);
}

bool ParticulaDinamica::expandir()
{
    if (m_fuerzas.empty())
        return true;

    bool hay_interaccion = false;
    for (Interaccion interaccion : m_interacciones)
    {
        for (std::shared_ptr<Fuerza> intercambio : m_fuerzas)
            hay_interaccion |= intercambio->aplicar(interaccion.normal, this, interaccion.particula);

        if (resultado)
            agregar_elemento(interaccion.particula);
    }

    return !hay_interaccion;
}

void ParticulaDinamica::actualizar()
{
    resetear();
    for (std::shared_ptr<Fuerza> intercambio : m_fuerzas)
        intercambio->actualizar();
}

bool ParticulaDinamica::puede_interactuar(Particula *referencia)
{
    return !en_historial(referencia);
}

/*
void Particula::velocidad_final()
{
    for (std::pair<Fuerza *, bool> intercambio : m_fuerzas)
        intercambio.first->modificar(m_velocidad, m_velocidad_angular, m_info);
}

void Particula::aplicar_torque(float torque)
{
    m_torque += torque;
}

void Particula::aplicar_fuerza(Vector2 fuerza)
{
    m_fuerza += fuerza;
    m_fuerza_guardada = m_fuerza;
}

bool Particula::choque_de_fuerzas(Particula *particula, Vector2 &normal, Caracteristica impacto)
{
    if (m_es_estatico || particula->en_historial(this))
        return false;

    Vector2 fuerza_resultante = m_fuerza.proyeccion(normal);

    if (fuerza_resultante * normal > 0)
    {
        // particula->m_fuerza_guardada += fuerza_resultante;
        particula->rotacion_por_choque(fuerza_resultante, impacto);

        // m_fuerza_guardada -= fuerza_resultante;
        rotacion_por_choque(fuerza_resultante * -1.0f, impacto);
        return true;
    }

    return false;
}

void Particula::rotacion_por_choque(Vector2 fuerza, Caracteristica impacto)
{
    for (int i = 0; i < impacto.cantidad(); i++)
    {
        // (impacto[i] - m_cuerpo->m_posicion).imprimir();
        m_torque += (impacto[i] - m_cuerpo->m_posicion).vectorial(fuerza);
    }
}

bool Particula::choque_de_velocidades(Particula *particula, Vector2 &normal, Caracteristica impacto)
{
    if (m_es_estatico || particula->en_historial(this))
        return false;

    Vector2 fuerza_choque = fuerza_de_choque(particula, normal);

    if (fuerza_choque * normal > 0 && m_velocidad * normal > 0)
    {
        particula->m_velocidad_guardada += fuerza_choque / particula->m_info->masa;
        // particula->rotacion_por_choque(fuerza_choque, impacto);

        m_velocidad_guardada -= fuerza_choque / m_info->masa;
        // rotacion_por_choque(fuerza_choque * -1.0f, impacto);
        return true;
    }

    return false;
}
*/

Vector2 ParticulaDinamica::velocidad()
{
    // for (std::pair<Fuerza *, bool> intercambio : m_fuerzas)
    //     intercambio.first->modificar(m_velocidad, m_velocidad_angular, m_info);
    return Vector2();
}

float ParticulaDinamica::velocidad_angular()
{
    return .0f;
}

// hay que corregirlo
Vector2 ParticulaDinamica::fuerza_de_choque(Particula *particula, Vector2 &direccion)
{
    // float masa = (particula->m_es_estatico) ? m_info->masa : particula->m_info->masa;
    // float coeficiente = (particula->m_es_estatico) ? m_coeficiente : particula->m_coeficiente;

    // float coeficiente_total = (m_coeficiente + coeficiente) / 4.0f + .5f;

    // Vector2 velocidad_relativa = velocidad().proyeccion(direccion) - particula->velocidad().proyeccion(direccion);
    // float promedio_de_masas = (m_info->masa + masa) / 2.0f;

    // Vector2 fuerza = (velocidad_relativa * m_info->masa * masa) / (promedio_de_masas);

    // return fuerza * coeficiente_total * (particula->m_es_estatico ? 2.0f : 1.0f);
    return Vector2();
}

ParticulaEstatica::ParticulaEstatica(cr::CuerpoRigido *cuerpo)
    : Particula(cuerpo)
{
}

bool ParticulaEstatica::expandir()
{
    return true;
}

void ParticulaEstatica::actualizar()
{
    resetear();
}

bool ParticulaEstatica::puede_interactuar(Particula *referencia)
{
    return false;
}

Vector2 ParticulaEstatica::velocidad()
{
    return Vector2();
}

float ParticulaEstatica::velocidad_angular()
{
    return .0f;
}