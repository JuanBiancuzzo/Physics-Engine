#pragma once

#include "vector.h"
#include "cuerpos/colisiones.h"
#include "sistema.h"

#include <vector>

namespace cc
{

    class Particula;

    class SistemaDeParticulas
    {
    public:
        std::vector<Particula *> m_particulas;
        float m_dt;

    public:
        SistemaDeParticulas(std::vector<Particula *> particulas, float dt);

        void avanzar_frame();
    };

    class Particula : public sistema::Particula
    {
    public:
        CuerpoRigido *m_cuerpo;

    public:
        Particula(float masa, CuerpoRigido *cuerpo, Vector2 velocidad, float coeficiente);

        void aplicar_fuerza(Vector2 fuerza);
    };

}
