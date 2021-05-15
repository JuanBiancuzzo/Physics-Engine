#include "ciruclo.h"
#include "linea.h"

#include "math.h"

namespace colision
{
    colision_circulo_circulo(Circulo *prin, Circulo *secun)
    {
        Vector2 A = (secun->m_pos - prin->m_pos).normal() * prin->m_radio;
        Vector2 B = (prin->m_pos - secun->m_pos).normal() * secun->m_radio;
        bool colisionan = pow(prin->m_radio + secun->m_radio, 2) >= (prin->m_pos - secun->m_pos).distancia_cuadrada());

        return {A, B, (B - A).normal(), (B - A).distancia(), colisionan};
    }

    colision_circulo_linea(Circulo *circulo, Linea *linea)
    {
    }
}