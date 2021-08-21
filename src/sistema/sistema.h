#pragma once

#include <vector>
#include <memory>

#include "../vector.h"
#include "../cuerpos/gjk.h"
#include "historial.h"
#include "particula.h"

namespace sistema
{

    class Particula;
    
    struct Interaccion
    {
        Particula *particula;
        Vector2 normal;
        Caracteristica impacto;
    };

    class Sistema
    {
    private:
        std::vector<Particula *> m_particulas;

    public:
        Sistema(std::vector<Particula *> particulas);

        void agregar_interaccion(Particula *particula, Particula *referencia);
        void expandir_interacciones();
    };
}