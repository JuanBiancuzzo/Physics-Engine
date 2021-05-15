#include "cuerpoRigido.h"

#include "ciruclo.h"
#include "linea.h"

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
        Vector2 B = linea->m_pos + (liena->m_final - linea->m_pos).proyeccion(circulo->m_pos - linea->m_pos);
        Vector2 A = (B - circulo->m_pos).normal() * circulo->m_radio;
        bool colisionan = circulo->m_radio >= (B - circulo->m_pos).modulo();

        return {A, B, (B - A).normal(), (B - A).modulo(), colisionan};
    }

    PuntoDeColision colision_linea_linea(Linea *prin, Linea *secun)
    {
        return {};
    }
}