#include "circulo.h"

using namespace cr;

Circulo::Circulo(Vector2 posicion, float radio)
    : CuerpoRigido(posicion), m_radio(radio)
{
}

Circulo::Circulo(Vector2 posicion, float rotacion, float radio)
    : CuerpoRigido(posicion, rotacion), m_radio(radio)
{
}

Vector2 Circulo::punto_soporte(Vector2 dir)
{
    return m_posicion + dir.normal() * m_radio;
}

sistema::Caracteristica Circulo::caracteristica_en_dir(Vector2 dir)
{
    sistema::Caracteristica caracteristica;
    Vector2 vertice = punto_soporte(dir);
    caracteristica.reemplazar_vertice(vertice);
    return caracteristica;
}

CuerpoRigido *Circulo::copia(Vector2 posicion)
{
    return new Circulo(m_posicion + posicion, m_rotacion, m_radio);
}

float Circulo::calcular_inercia(float masa)
{
    return .5f * masa * m_radio * m_radio;
}