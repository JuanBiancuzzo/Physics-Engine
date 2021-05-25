#pragma once

#include "AABB.h"
#include "linea.h"
#include "circulo.h"

namespace colision
{
    PuntoDeColision colision_circulo_circulo(Circulo *, Circulo *);

    PuntoDeColision colision_circulo_linea(Circulo *, Linea *);

    PuntoDeColision colision_linea_linea(Linea *, Linea *);

    PuntoDeColision colision_aabb_aabb(AABB *, AABB *);

    PuntoDeColision colision_circulo_aabb(Circulo *, AABB *);

    PuntoDeColision colision_aabb_linea(AABB *, Linea *);
}