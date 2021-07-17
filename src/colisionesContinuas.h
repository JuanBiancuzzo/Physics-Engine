#pragma once

#include "cuerpos/gjk.h"
#include "quadtree.h"
#include "sistema.h"

#include <vector>
#include <array>

namespace cc
{

    class Particula;
    struct Linea;

    class SistemaDeParticulas
    {
    public:
        qt::QuadTree m_area;
        std::vector<Particula *> m_particulas;
        float m_dt;

    public:
        SistemaDeParticulas(cr::AABB &area, std::vector<Particula *> particulas, float dt);

        void avanzar_frame();

    private:
        void interaccion(Particula *particula1, Particula *particula2);
    };

    class Particula : public sistema::Particula, public qt::Entidad
    {
    public:
        cr::CuerpoRigido *m_cuerpo;
        float m_dt;

    public:
        Particula(float masa, cr::CuerpoRigido *cuerpo, Vector2 velocidad, float coeficiente);

        void aplicar_fuerza(Vector2 fuerza);
        void actualizar(float dt);
        bool colisiona(cr::CuerpoRigido *area);
        Vector2 diferencia_posicion(Particula *particula);
        std::array<Linea, 2> extremos_de_camino();

    private:
        Vector2 posicion_futura();
    };

    struct Colision 
    {
        Particula *particula1, *particula2;
        float tiempo_de_choque;
    };

    struct Linea
    {
        Vector2 m_inicio, m_final;

        float punto_contacto(Linea linea);
    };
}
