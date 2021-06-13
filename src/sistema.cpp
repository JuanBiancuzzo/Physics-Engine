#include "sistema.h"

using namespace sistema;

Sistema::Sistema(std::vector<Particula *> &particulas)
{
    for (Particula *particula : particulas)
        m_grafo.agregar_node(particula);
}

void Sistema::expandir_fuerzas()
{
    std::vector<grafo::Node *> primeros = m_grafo.primeros();
    m_grafo.expandir_interaccion(primeros);
}

Particula::Particula(Vector2 fuerza)
    : m_acumulador_total(fuerza)
{
}

Interaccion::Interaccion(Vector2 direccion)
    : m_direccion(direccion)
{
}

bool Interaccion::valido(Particula *particula)
{
    return (m_direccion * particula->m_acumulador_total) > 0;
}
