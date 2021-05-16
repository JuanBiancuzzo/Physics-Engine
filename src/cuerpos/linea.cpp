#include "linea.h"

#include "colisiones.cpp"

Linea::Linea(Vector2 principio, Vector2 final)
    : CuerpoRigido(principio), m_final(final)
{
}

PuntoDeColision Linea::colisiona(CuerpoRigido *cuerpo_rigido)
{
    return cuerpo_rigido->colisiona(this);
}

PuntoDeColision Linea::colisiona(Circulo *circulo)
{
    return colision::colision_circulo_linea(circulo, this).invertir();
}

PuntoDeColision Linea::colisiona(Linea *linea)
{
    return colision::colision_linea_linea(this, linea);
}

PuntoDeColision Linea::colisiona(AABB *aabb)
{
    return colision::colision_aabb_linea(aabb, this).invertir();
}
