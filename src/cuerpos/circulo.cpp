
#include "ciruclo.h"

#include "colisiones.cpp"

Circulo::Circulo(Vector2 posicion, float radio)
    : CuerpoRigido(posicion), m_radio(radio)
{
}

PuntoDeColision Circulo::colisiona(CuerpoRigido *cuerpo_rigido)
{
    return cuerpo_rigido->colisiona(this);
}

PuntoDeColision Circulo::colisiona(Circulo *circulo)
{
    return colision::colision_circulo_circulo(this, circulo);
}

PuntoDeColision Circulo::colisiona(Linea *linea)
{
    return colision::colision_circulo_linea(this, linea);
}

PuntoDeColision Circulo::colisiona(AABB *aabb)
{
    return colision::colision_circulo_aabb(this, aabb);
}