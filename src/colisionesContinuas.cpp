#include "colisionesContinuas.h"

using namespace cc;

SistemaDeParticulas::SistemaDeParticulas(cr::AABB &area, std::vector<Particula *> particulas, float dt)
    : m_area(area), m_particulas(particulas), m_dt(dt)
{
    for (Particula *particula : particulas)
        m_area.insertar(particula->crear_cuerpo_extendido());
}

void SistemaDeParticulas::avanzar_frame()
{
    std::array<Linea, 2> primeros = m_particulas[0]->extremos_de_camino();
    std::array<Linea, 2> segundos = m_particulas[1]->extremos_de_camino();

    float tiempo_choque = 1.0f;
    for (Linea segundo : segundos)
    {
        float extremos = .0f;
        for (Linea primero : primeros)
            extremos += primero.punto_contacto(segundo);
        tiempo_choque = std::min(tiempo_choque, extremos / 2);
    }

    for (Particula *particula : m_particulas)
        particula->actualizar(tiempo_choque);

    interaccion(m_particulas[0], m_particulas[1]);

    for (Particula *particula : m_particulas)
        particula->actualizar(1.0f - tiempo_choque);
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

Particula::Particula(float masa, cr::CuerpoRigido *cuerpo, Vector2 velocidad, float coeficiente)
    : m_cuerpo(cuerpo), m_dt(1.0f), sistema::Particula(masa, velocidad, Vector2(), coeficiente), m_cuerpo_extendido(nullptr)
{
}

Particula::~Particula()
{
    if (!m_cuerpo_extendido)
        delete m_cuerpo_extendido;
}

void Particula::actualizar(float dt)
{
    m_velocidad += m_fuerza * dt / m_masa;
    m_cuerpo->m_posicion += m_velocidad * dt;
    m_fuerza *= 0;
}

Vector2 Particula::diferencia_posicion(Particula *particula)
{
    return particula->m_cuerpo->m_posicion - m_cuerpo->m_posicion;
}

std::array<Linea, 2> Particula::extremos_de_camino()
{
    Vector2 posicon_futura = this->posicion_futura();
    Vector2 direccion = (posicon_futura - m_cuerpo->m_posicion).normal();
    Vector2 perpendicular = Vector2(direccion.y * -1.0f, direccion.x);

    Vector2 punto_inicio_1 = m_cuerpo->punto_soporte(perpendicular);
    Vector2 punto_final_1 = perpendicular + posicon_futura;
    Linea linea_1 = {punto_inicio_1, punto_final_1};

    perpendicular *= -1.0f;
    Vector2 punto_inicio_2 = m_cuerpo->punto_soporte(perpendicular);
    Vector2 punto_final_2 = perpendicular + posicon_futura;
    Linea linea_2 = {punto_inicio_2, punto_final_2};

    return {linea_1, linea_2};
}

Vector2 Particula::posicion_futura()
{
    Vector2 velocidad = m_velocidad + (m_fuerza * m_dt / m_masa);
    Vector2 posicion = m_cuerpo->m_posicion + velocidad * m_dt;
    return posicion;
}

CuerpoExtendido *Particula::crear_cuerpo_extendido()
{
    Vector2 posicion_final = posicion_futura();
    cr::CuerpoRigido *cuerpo_futuro = m_cuerpo->copia(posicion_final);
    m_cuerpo_extendido = new CuerpoExtendido(m_cuerpo, cuerpo_futuro);
    return m_cuerpo_extendido;
}

CuerpoExtendido::CuerpoExtendido(cr::CuerpoRigido *cuerpo_inicio, cr::CuerpoRigido *cuerpo_final)
    : m_inicio(cuerpo_inicio), m_final(cuerpo_final)
{
}

bool CuerpoExtendido::colisiona(cr::CuerpoRigido *area)
{
    bool cuerpo_inicio = false, cuerpo_final = false;
    cuerpo_inicio = m_inicio->colisiona(area).colisiono;
    if (!cuerpo_inicio)
        cuerpo_final = m_final->colisiona(area).colisiono;
    return cuerpo_inicio || cuerpo_final;
}

float Linea::punto_contacto(Linea linea)
{
    Vector2 punto_inicio = m_inicio - linea.m_inicio;
    Vector2 punto_final = linea.m_final - linea.m_inicio - m_final + m_inicio;

    return std::min(punto_inicio.x / punto_final.x, punto_inicio.y / punto_final.y);
}