#include "cuerpoRigido.h"
#include "gjk.h"

using namespace cr;

CuerpoRigido::CuerpoRigido(float masa, Vector2 posicion, float rotacion)
    : m_posicion(posicion), m_rotacion(rotacion), m_masa(masa)
{
}

CuerpoRigido::CuerpoRigido(Vector2 posicion)
    : m_posicion(posicion), m_rotacion(.0f), m_masa(1.0f)
{
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

    Vector2 diferencia = cuerpo_rigido->m_posicion - m_posicion;
    float distancia = diferencia.modulo();
    Vector2 normal = diferencia.normal();

    return {punto_soporte(normal), cuerpo_rigido->punto_soporte(normal * -1.0f), normal, distancia, gjk.colisionan()};
}

bool CuerpoRigido::colisiona(CuerpoRigido *cuerpo_rigido)
{
    Gjk gjk(this, cuerpo_rigido);

    Vector2 diferencia = cuerpo_rigido->m_posicion - m_posicion;
    float distancia = diferencia.modulo();
    Vector2 normal = diferencia.normal();

    return gjk.colisionan();
}