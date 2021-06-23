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
    : m_masa(masa), m_velocidad(velocidad), m_fuerza(fuerza), m_estatico(false)
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

    return ((particula->m_fuerza) * m_direccion > 0) || (particula->sum_vel(p_referencia) * m_direccion > 0);
}

void Interaccion::expandir(grafo::Node *node, grafo::Node *referencia)
{
    Particula *particula = static_cast<Particula *>(node);
    Particula *p_referencia = static_cast<Particula *>(referencia);
    Vector2 fuerza;

    if (!particula->m_estatico)
        fuerza += particula->m_fuerza.proyeccion(m_direccion);
    if (particula->sum_vel(p_referencia) * m_direccion > 0)
        fuerza += ((particula->sum_vel(p_referencia) * m_dt) / particula->m_masa).proyeccion(m_direccion);

    if (fuerza * m_direccion > 0)
    {
        p_referencia->m_fuerza += (!p_referencia->m_estatico) ? fuerza : fuerza * -1.0f;
        particula->m_fuerza -= fuerza;
    }
}
