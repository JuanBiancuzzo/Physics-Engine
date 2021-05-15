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
    PuntoDeColision punto = colision::colision_circulo_linea(circulo, this);

    Vector2 temp = punto.B;
    punto.B = punto.A;
    punto.A = temp;
    punto.normal *= -1.0f;

    return punto;
}

PuntoDeColision Linea::colisiona(Linea *linea)
{
    return colision::colision_linea_linea(this, linea);
}
