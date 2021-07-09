#include "linea.h"

Linea::Linea(Vector2 principio, Vector2 final)
    : CuerpoRigido(principio), m_final(final)
{
}

Vector2 Linea::punto_soporte(Vector2 dir)
{
    if (m_final * dir > m_posicion * dir)
        return m_final;
    return m_posicion;
}
