#pragma once

#include "cuerpoRigido.h"

class AABB : public CuerpoRigido
{
public:
    float m_ancho, m_alto;

public:
    AABB(Vector2 posicion, float ancho, float alto);

    PuntoDeColision colisiona(CuerpoRigido *cuerpo_rigido);
    PuntoDeColision colisiona(Circulo *circulo);
    PuntoDeColision colisiona(Linea *linea);
    PuntoDeColision colisiona(AABB *aabb);

private:
    Vector2 punto_borde(const Vector2 &direccion) const;
};