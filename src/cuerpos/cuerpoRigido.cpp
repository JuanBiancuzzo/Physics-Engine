#include "cuerpoRigido.h"
#include "gjk.h"

using namespace cr;

CuerpoRigido::CuerpoRigido(Vector2 posicion)
    : m_posicion(posicion)
{
}

PuntoDeColision CuerpoRigido::punto_de_colision(CuerpoRigido *cuerpo_rigido)
{
    Gjk gjk(this, cuerpo_rigido);

    Vector2 diferencia = cuerpo_rigido->m_posicion - m_posicion;
    float distancia = diferencia.modulo();
    Vector2 normal = diferencia.normal();

    return {normal, distancia, gjk.colisionan()};
}

bool CuerpoRigido::colisiona(CuerpoRigido *cuerpo_rigido)
{
    Gjk gjk(this, cuerpo_rigido);

    Vector2 diferencia = cuerpo_rigido->m_posicion - m_posicion;
    float distancia = diferencia.modulo();
    Vector2 normal = diferencia.normal();

    return gjk.colisionan();
}