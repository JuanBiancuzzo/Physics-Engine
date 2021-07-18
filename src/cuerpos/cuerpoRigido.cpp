#include "cuerpoRigido.h"
#include "gjk.h"

using namespace cr;

CuerpoRigido::CuerpoRigido(float masa, Vector2 posicion, float rotacion)
    : m_posicion(posicion), m_rotacion(rotacion), m_masa(masa), m_inercia(calcular_inercia())
{
}

CuerpoRigido::CuerpoRigido(Vector2 posicion)
    : m_posicion(posicion), m_rotacion(.0f), m_masa(1.0f), m_inercia(calcular_inercia())
{
}

float CuerpoRigido::calcular_inercia()
{
    return .0f;
}

void CuerpoRigido::modificar_posicion(Vector2 valor)
{
    m_posicion += valor;
}

void CuerpoRigido::modificar_rotacion(float valor)
{
    m_rotacion += valor;
}

PuntoDeColision CuerpoRigido::punto_de_colision(CuerpoRigido *cuerpo_rigido)
{
    Gjk gjk(this, cuerpo_rigido);

    return gjk.info_colision();
}

bool CuerpoRigido::colisiona(CuerpoRigido *cuerpo_rigido)
{
    Gjk gjk(this, cuerpo_rigido);

    return gjk.colisionan();
}