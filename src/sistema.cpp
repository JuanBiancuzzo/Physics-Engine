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
    Interaccion *interaccion = new Interaccion(direccion);
    m_grafo.agregar_arista(particula, referencia, interaccion);
    m_interacciones.emplace_back(interaccion);
}

void Sistema::expandir_fuerzas()
{
    std::vector<grafo::Node *> primeros = m_grafo.primeros();
    m_grafo.expandir_interaccion(primeros);
}

Particula::Particula(float masa, Vector2 &velocidad, Vector2 &fuerza)
    : m_masa(masa), m_velocidad(velocidad), m_fuerza(fuerza), m_estatico(true)
{
}

Particula::Particula(bool es_estatico)
    : m_masa(.0f), m_estatico(true)
{
}

Vector2 Particula::fuerza_final()
{
    return m_fuerza;
}

Interaccion::Interaccion(Vector2 &direccion)
    : m_direccion(direccion)
{
}

bool Interaccion::valido(grafo::Node *node)
{
    Particula *particula = static_cast<Particula *>(node);
    return (m_direccion * particula->m_fuerza) > 0;
}

void Interaccion::expandir(grafo::Node *node, grafo::Node *referencia)
{
    Particula *particula = static_cast<Particula *>(node);
    Particula *p_referencia = static_cast<Particula *>(referencia);

    if (!particula->m_estatico)
    {
        Vector2 fuerza = particula->m_fuerza.proyeccion(m_direccion);

        p_referencia->m_fuerza += (!p_referencia->m_estatico) ? fuerza : (fuerza * -1.0f);
        particula->m_fuerza -= fuerza;
    }
}
