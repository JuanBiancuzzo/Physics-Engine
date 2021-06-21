#include "sistema.h"

using namespace sistema;

Sistema::Sistema(std::vector<Particula *> &particulas)
{
    for (Particula *particula : particulas)
        m_grafo.agregar_node(particula);
}

void Sistema::agreagar_interaccion(Particula *particula, Particula *referencia, Interaccion *interaccion)
{
    m_grafo.agregar_arista(particula, referencia, interaccion);
}

void Sistema::expandir_fuerzas()
{
    std::vector<grafo::Node *> primeros = m_grafo.primeros();
    m_grafo.expandir_interaccion(primeros);
}

Particula::Particula(Vector2 &fuerza_inicial, Vector2 &fuerza_velocidad)
    : m_fuerza(fuerza_inicial), m_fuerza_velocidad(fuerza_velocidad), m_estatico(false)
{
}

Particula::Particula(bool es_estatico)
    : m_estatico(true)
{
}

Interaccion::Interaccion(Vector2 &direccion)
    : m_direccion(direccion)
{
}

bool Interaccion::valido(grafo::Node *node)
{
    Particula *particula = static_cast<Particula *>(node);
    return (m_direccion * (particula->m_fuerza + particula->m_fuerza_velocidad)) > 0;
}

void Interaccion::expandir(grafo::Node *node, grafo::Node *referencia)
{
    Particula *particula = static_cast<Particula *>(node);
    Particula *p_referencia = static_cast<Particula *>(referencia);

    Vector2 fuerza = (particula->m_fuerza + particula->m_fuerza_velocidad).proyeccion(m_direccion);

    p_referencia->m_fuerza += fuerza * (-2.0f * p_referencia->m_estatico + 1.0f);
    particula->m_fuerza -= fuerza;
}
