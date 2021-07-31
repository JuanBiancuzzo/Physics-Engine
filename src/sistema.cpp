#include "sistema.h"

using namespace sistema;

template <typename T>
bool insertar_sin_repetir(std::vector<T> &lista, T elemento)
{
    for (T e : lista)
        if (e == elemento)
            return false;
    lista.emplace_back(elemento);
    return true;
}

Sistema::Sistema(std::vector<Particula *> particulas)
    : m_particulas(particulas)
{
}

void Sistema::agregar_interaccion(Particula *particula, Particula *referencia)
{
    particula->agregar_interaccion(referencia);
}

void Sistema::expandir_interacciones()
{
    bool terminado = false;
    for (int i = 0; i < 10 && !terminado; i++)
    {
        terminado = true;
        for (Particula *particula : m_particulas)
            terminado &= particula->expandir();

        for (Particula *particula : m_particulas)
            particula->actualizar();
    }
}

Particula::Particula(cr::CuerpoRigido *cuerpo, Vector2 velocidad, float velocidad_angular, float coeficiente)
    : m_cuerpo(cuerpo), m_velocidad(velocidad), m_velocidad_angular(velocidad_angular), m_torque(.0f), m_coeficiente(coeficiente),
      m_velocidad_guardada(velocidad), m_es_estatico(false)
{
}

Particula::Particula(cr::CuerpoRigido *cuerpo)
    : m_cuerpo(cuerpo), m_es_estatico(true)
{
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

bool Particula::visitaste(Particula *particula)
{
    for (Particula *p : m_historial)
        if (p == particula)
            return true;
    return false;
}

bool Particula::expandir()
{
    if ((m_fuerza.nulo() && m_velocidad.nulo()) || m_es_estatico)
        return true;

    bool hay_interaccion = false;
    for (Interaccion interaccion : m_interacciones)
    {
        bool resultado = this->choque_de_fuerzas(interaccion.particula, interaccion.normal, interaccion.impacto);
        resultado |= this->choque_de_velocidades(interaccion.particula, interaccion.normal, interaccion.impacto);
        if (resultado)
            m_historial.emplace_back(interaccion.particula);
        hay_interaccion |= resultado;
    }

    return !hay_interaccion;
}

void Particula::actualizar()
{
    if (!m_es_estatico)
    {
        m_velocidad = m_velocidad_guardada;
        m_fuerza = m_fuerza_guardada;
    }
    m_historial.clear();
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

bool Particula::choque_de_fuerzas(Particula *particula, Vector2 &normal, cr::Caracteristica impacto)
{
    if (m_es_estatico || particula->visitaste(this))
        return false;

    Vector2 fuerza_resultante = m_fuerza.proyeccion(normal);

    if (fuerza_resultante * normal > 0)
    {
        particula->m_fuerza_guardada += fuerza_resultante;
        particula->rotacion_por_choque(fuerza_resultante, impacto);

        m_fuerza_guardada -= fuerza_resultante;
        rotacion_por_choque(fuerza_resultante * -1.0f, impacto);
        return true;
    }

    return false;
}

void Particula::rotacion_por_choque(Vector2 fuerza, cr::Caracteristica impacto)
{
    for (int i = 0; i < impacto.cantidad(); i++)
    {
        // (impacto[i] - m_cuerpo->m_posicion).imprimir();
        m_torque += (impacto[i] - m_cuerpo->m_posicion).vectorial(fuerza);
    }
}

bool Particula::choque_de_velocidades(Particula *particula, Vector2 &normal, cr::Caracteristica impacto)
{
    if (m_es_estatico || particula->visitaste(this))
        return false;

    Vector2 fuerza_choque = fuerza_de_choque(particula, normal);

    if (fuerza_choque * normal > 0 && m_velocidad * normal > 0)
    {
        particula->m_velocidad_guardada += fuerza_choque / particula->m_cuerpo->m_masa;
        particula->rotacion_por_choque(fuerza_choque, impacto);

        m_velocidad_guardada -= fuerza_choque / m_cuerpo->m_masa;
        rotacion_por_choque(fuerza_choque * -1.0f, impacto);
        return true;
    }

    return false;
}

Vector2 Particula::fuerza_de_choque(Particula *particula, Vector2 &direccion)
{
    float masa = (particula->m_es_estatico) ? m_cuerpo->m_masa : particula->m_cuerpo->m_masa;
    float coeficiente = (particula->m_es_estatico) ? m_coeficiente : particula->m_coeficiente;

    float coeficiente_total = (m_coeficiente + coeficiente) / 4.0f + .5f;

    Vector2 velocidad_relativa = velocidad_en_direccion(direccion) - particula->velocidad_en_direccion(direccion);
    float promedio_de_masas = (m_cuerpo->m_masa + masa) / 2.0f;

    Vector2 fuerza = (velocidad_relativa * m_cuerpo->m_masa * masa) / (promedio_de_masas);

    return fuerza * coeficiente_total * (particula->m_es_estatico ? 2.0f : 1.0f);
}

Vector2 Particula::velocidad_en_direccion(Vector2 &direccion)
{
    return m_velocidad.proyeccion(direccion);
}
