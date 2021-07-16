#include "colisionesContinuas.h"

using namespace cc;

SistemaDeParticulas::SistemaDeParticulas(std::vector<Particula *> particulas, float dt)
    : m_particulas(particulas), m_dt(dt)
{
}

void SistemaDeParticulas::avanzar_frame()
{
}

Particula::Particula(float masa, CuerpoRigido *cuerpo, Vector2 velocidad, float coeficiente)
    : m_cuerpo(cuerpo), sistema::Particula(masa, velocidad, Vector2(), coeficiente)
{
}
