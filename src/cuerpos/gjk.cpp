#include "gjk.h"

Gjk::Gjk(CuerpoRigido *cuerpo1, CuerpoRigido *cuerpo2)
    : m_cuerpo1(cuerpo1), m_cuerpo2(cuerpo2)
{
}

bool Gjk::colisionan()
{
    Vector2 dir = (m_cuerpo2->m_posicion - m_cuerpo1->m_posicion).normal();
    Simplex simplex(soporte(dir));
    dir *= -1.0f; // vector direccion del punto hasta el origen

    Vector2 vertice = soporte(dir);
    while (vertice * dir >= .0f)
    {
        simplex.agregar_vertice(vertice);
        if (simplex.contiene_origen(dir))
            return true;

        Vector2 vertice = soporte(dir);
    }
    return false;
}

Vector2 Gjk::soporte(Vector2 &dir)
{
    return (m_cuerpo1->punto_soporte(dir) - m_cuerpo2->punto_soporte(dir * -1.0f));
}

Simplex::Simplex(Vector2 primer_vertice)
    : A(primer_vertice)
{
    m_cantidad++;
}

void Simplex::agregar_vertice(Vector2 &vertice)
{
    C = B;
    B = A;
    A = vertice;
    m_cantidad += (m_cantidad <= 2);
}

bool Simplex::contiene_origen(Vector2 &dir)
{
    if (m_cantidad == 2)
        return caso_linea(dir);
    return caso_triangulo(dir);
}

bool Simplex::caso_linea(Vector2 &dir) // agregar caso donde esta en el borde
{
    Vector2 origen = Vector2();

    Vector2 ABperp = A.perp_en_dir(B, origen);
    dir = ABperp;

    // if (-.1f < ABperp * (O - A) && ABperp * (O - A) < .1f)
    //     return true;

    return false;
}

bool Simplex::caso_triangulo(Vector2 &dir)
{
    Vector2 origen = Vector2(), AO = A * -1.0f;

    Vector2 ABperp = A.perp_en_dir(B, origen);
    if (ABperp * AO > 0)
    {
        // eliminar C es no hacer nada
        dir = ABperp;
        return false;
    }

    Vector2 ACperp = A.perp_en_dir(C, origen);
    if (ACperp * AO > 0)
    {
        B = C; // eliminamos B
        dir = ACperp;
        return false;
    }

    return true;
}