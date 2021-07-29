#include "circulo.h"

using namespace cr;

Circulo::Circulo(Vector2 posicion, float radio)
    : CuerpoRigido(posicion), m_radio(radio)
{
    m_inercia = calcular_inercia();
}

Circulo::Circulo(float masa, Vector2 posicion, float rotacion, float radio)
    : CuerpoRigido(masa, posicion, rotacion), m_radio(radio)
{
    m_inercia = calcular_inercia();
}

Vector2 Circulo::punto_soporte(Vector2 dir)
{
    return m_posicion + dir.normal() * m_radio;
}

Caracteristica Circulo::caracteristica_en_dir(Vector2 dir)
{
    Caracteristica caracteristica;
    Vector2 vertice = punto_soporte(dir);
    caracteristica.reemplazar_vertice(vertice);
    return caracteristica;
}

CuerpoRigido *Circulo::copia(Vector2 posicion)
{
    return new Circulo(m_masa, m_posicion + posicion, m_rotacion, m_radio);
}

float Circulo::calcular_inercia()
{
    return .5f * m_masa * m_radio * m_radio;
}