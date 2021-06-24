#include "sistema.h"

using namespace sistema;

Sistema::Sistema(float dt)
    : m_dt(dt)
{
}

Sistema::~Sistema()
{
    for (Interaccion *interaccion : m_interacciones)
        delete interaccion;
}

void Sistema::agregar_particula(Particula *particula)
{
    m_grafo.agregar_node(particula);
}

void Sistema::agregar_interaccion(Particula *particula, Particula *referencia, Vector2 direccion)
{
    Interaccion *interaccion = new Interaccion(direccion, m_dt);
    m_grafo.agregar_arista(particula, referencia, interaccion);
    m_interacciones.emplace_back(interaccion);
}

void Sistema::expandir_fuerzas()
{
    std::vector<grafo::Node *> primeros = m_grafo.primeros();
    m_grafo.expandir_interaccion(primeros);
}

Particula::Particula(float masa, Vector2 &velocidad, Vector2 &fuerza)
    : m_masa(masa), m_velocidad(velocidad), m_fuerza(fuerza), m_fuerza_inicial(fuerza), m_estatico(false)
{
}

Vector2 Particula::sum_vel(Particula *particula)
{
    return (m_velocidad + particula->m_velocidad);
}

Particula::Particula(bool es_estatico)
    : m_masa(.0f), m_estatico(true)
{
}

Interaccion::Interaccion(Vector2 &direccion, float dt)
    : m_direccion(direccion), m_dt(dt)
{
}

bool Interaccion::valido(grafo::Node *node, grafo::Node *referencia)
{
    Particula *particula = static_cast<Particula *>(node);
    Particula *p_referencia = static_cast<Particula *>(referencia);

    return ((particula->m_fuerza) * m_direccion > 0 || particula->m_velocidad * m_direccion > 0);
}

void Interaccion::expandir(grafo::Node *node, grafo::Node *referencia)
{
    Particula *particula = static_cast<Particula *>(node);
    Particula *p_referencia = static_cast<Particula *>(referencia);
    Vector2 velocidad_de_choque = particula->m_velocidad - p_referencia->m_velocidad;
    Vector2 fuerza, impulso;

    if (!particula->m_estatico && particula->m_fuerza * m_direccion > 0)
        // if (particula->m_fuerza * m_direccion > 0)
        fuerza += particula->m_fuerza.proyeccion(m_direccion);
    if (velocidad_de_choque * m_direccion > 0)
        impulso += (velocidad_de_choque / m_dt).proyeccion(m_direccion);

    // p_referencia->m_fuerza += (impulso * p_referencia->m_masa) * (!p_referencia->m_estatico ? 1.0f : -1.0f);
    p_referencia->m_fuerza += (fuerza + impulso * p_referencia->m_masa) * (!p_referencia->m_estatico ? 1.0f : -1.0f);
    // p_referencia->m_fuerza += (fuerza + impulso * p_referencia->m_masa - p_referencia->m_fuerza_inicial) * (!p_referencia->m_estatico ? 1.0f : -1.0f);
    particula->m_fuerza -= (fuerza + impulso * particula->m_masa);
    // particula->m_fuerza -= (fuerza + impulso * particula->m_masa) - particula->m_fuerza_inicial.proyeccion(m_direccion);
}
