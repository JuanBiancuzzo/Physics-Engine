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
    gjk::Gjk gjk(this, cuerpo_rigido);
    gjk::Info_colision info = gjk.info_de_colision();

    // Caracteristica *cuerpo1 = this->caracteristica_en_dir(info.normal);
    // Caracteristica *cuerpo2 = cuerpo_rigido->caracteristica_en_dir(info.normal * -1.0f); // revisar el signo
    // Caracteristica *interseccion = cuerpo1->interseccion(cuerpo2);
    // return {interseccion, info.normal, info.colision};

    return gjk.info_colision();
}

bool CuerpoRigido::colisiona(CuerpoRigido *cuerpo_rigido)
{
    gjk::Gjk gjk(this, cuerpo_rigido);

    return gjk.colisionan();
}