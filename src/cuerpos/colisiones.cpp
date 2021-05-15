#include "cuerpoRigido.h"

#include "ciruclo.h"
#include "linea.h"

#include <math.h>

namespace colision
{
    PuntoDeColision colision_circulo_circulo(Circulo *prin, Circulo *secun)
    {
        Vector2 A = (secun->m_pos - prin->m_pos).normal() * prin->m_radio;
        Vector2 B = (prin->m_pos - secun->m_pos).normal() * secun->m_radio;
        bool colisionan = prin->m_radio + secun->m_radio >= (prin->m_pos - secun->m_pos).modulo();

        return {A, B, (B - A).normal(), (B - A).modulo(), colisionan};
    }

    PuntoDeColision colision_circulo_linea(Circulo *circulo, Linea *linea)
    {
        return {};
    }

    PuntoDeColision colision_linea_linea(Linea *prin, Linea *secun)
    {
        return {};
    }
}