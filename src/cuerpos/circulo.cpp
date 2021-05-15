
#include "ciruclo.h"

Circulo::Circulo(float radio)
    : m_radio(radio)
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
