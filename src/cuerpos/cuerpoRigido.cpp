#include "cuerpoRigido.h"
#include "gjk.h"

using namespace cr;

CuerpoRigido::CuerpoRigido(Vector2 posicion, float rotacion)
    : m_posicion(posicion), m_rotacion(rotacion)
{
}

CuerpoRigido::CuerpoRigido(Vector2 posicion)
    : m_posicion(posicion), m_rotacion(.0f)
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
    gjk::Gjk gjk(this, cuerpo_rigido);
    gjk::Info_colision info = gjk.info_de_colision();

    sistema::Caracteristica cuerpo1 = this->caracteristica_en_dir(info.normal);
    sistema::Caracteristica cuerpo2 = cuerpo_rigido->caracteristica_en_dir(info.normal * -1.0f);
    sistema::Caracteristica interseccion = cuerpo1.intersecta(cuerpo2);

    return {interseccion, info.normal, info.colision};
}

bool CuerpoRigido::colisiona(CuerpoRigido *cuerpo_rigido)
{
    gjk::Gjk gjk(this, cuerpo_rigido);

    return gjk.colisionan();
}
