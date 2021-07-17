#pragma once

#include "cuerpos/gjk.h"
#include "quadtree.h"
#include "sistema.h"

#include <vector>
#include <array>

namespace cc
{

    class Particula;
    class CuerpoExtendido;
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

    class Particula : public sistema::Particula
    {
    public:
        cr::CuerpoRigido *m_cuerpo;
        float m_dt;
        CuerpoExtendido *m_cuerpo_extendido;

    public:
        Particula(float masa, cr::CuerpoRigido *cuerpo, Vector2 velocidad, float coeficiente);
        ~Particula();

        void aplicar_fuerza(Vector2 fuerza);
        void actualizar(float dt);
        Vector2 diferencia_posicion(Particula *particula);
        std::array<Linea, 2> extremos_de_camino();
        CuerpoExtendido *crear_cuerpo_extendido();

    private: 
        Vector2 posicion_futura();
    };

    struct Colision
    {
        Particula *particula1, *particula2;
        float tiempo_de_choque;
    };

    class CuerpoExtendido : public qt::Entidad
    {
    public:
        cr::CuerpoRigido *m_inicio, *m_final;
        // cr::Poligono<4> m_poligono; buscar una forma para agregarlo por ahora no tengo los vertices

    public:
        CuerpoExtendido(cr::CuerpoRigido *cuerpo_inicio, cr::CuerpoRigido *cuerpo_final);
        bool colisiona(cr::CuerpoRigido *area);
    };

    struct Linea
    {
        Vector2 m_inicio, m_final;

        float punto_contacto(Linea linea);
    };
}
