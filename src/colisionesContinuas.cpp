#include "colisionesContinuas.h"

using namespace cc;

SistemaDeParticulas::SistemaDeParticulas(std::vector<Particula *> particulas, float dt)
    : m_particulas(particulas), m_dt(dt)
{
}

void SistemaDeParticulas::avanzar_frame()
{
    int subdivision = 10000;
    float ddt = m_dt / subdivision;
    int contador = 0;

    for (int i = 0; i < subdivision; i++)
    {
        for (int i = 0; i < m_particulas.size(); i++)
            for (int j = i + 1; j < m_particulas.size(); j++)
                if (m_particulas[i]->m_cuerpo->colisiona(m_particulas[j]->m_cuerpo).colisiono)
                    interaccion(m_particulas[i], m_particulas[j]);

        for (Particula *particula : m_particulas)
            particula->actualizar(ddt);
    }
}

void SistemaDeParticulas::interaccion(Particula *particula1, Particula *particula2)
{
    sistema::Sistema sistema({particula1, particula2});
    Vector2 direccion_1_2 = particula1->diferencia_posicion(particula2);
    Vector2 direccion_2_1 = particula2->diferencia_posicion(particula1);
    sistema.agregar_interaccion(particula1, particula2, direccion_1_2);
    sistema.agregar_interaccion(particula1, particula2, direccion_2_1);
    sistema.expandir_interacciones();
}

Particula::Particula(float masa, CuerpoRigido *cuerpo, Vector2 velocidad, float coeficiente)
    : m_cuerpo(cuerpo), sistema::Particula(masa, velocidad, Vector2(), coeficiente)
{
}

void Particula::actualizar(float dt)
{
    m_velocidad += m_fuerza * dt / m_masa;
    m_cuerpo->m_posicion += m_velocidad * dt;
}

Vector2 Particula::diferencia_posicion(Particula *particula)
{
    return particula->m_cuerpo->m_posicion - m_cuerpo->m_posicion;
}
