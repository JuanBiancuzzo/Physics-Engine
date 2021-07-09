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

    while (true)
    {
        Vector2 vertice = soporte(dir);
        if (vertice * dir < 0)
            return false;
        simplex.agregar_vertice(vertice);
        if (simplex.contiene_origen(dir))
            return true;
    }
}

Vector2 Gjk::soporte(Vector2 &dir)
{
    return (m_cuerpo1->punto_soporte(dir) - m_cuerpo2->punto_soporte(dir * -1.0f));
}

Simplex::Simplex(Vector2 primer_vertice)
{
    agregar_vertice(primer_vertice);
}

void Simplex::agregar_vertice(Vector2 &vertice)
{
    m_vertices.emplace_back(vertice);
}

bool Simplex::contiene_origen(Vector2 &dir)
{
    if (m_vertices.size() == 2)
        return caso_linea(dir);
    return caso_triangulo(dir);
}

bool Simplex::caso_linea(Vector2 &dir) // agregar caso donde esta en el borde
{
    Vector2 B = m_vertices[0], A = m_vertices[1], O = Vector2();

    Vector2 ABperp = A.perp_en_dir(B, O);
    dir = ABperp;
    return false;
}

bool Simplex::caso_triangulo(Vector2 &dir)
{
    Vector2 C = m_vertices[0], B = m_vertices[1], A = m_vertices[2], O = Vector2(), AO = A * -1.0f;

    Vector2 ABperp = A.perp_en_dir(B, O);
    if (ABperp * AO > 0)
    {
        m_vertices.erase(m_vertices.begin());
        dir = ABperp;
        return false;
    }

    Vector2 ACperp = A.perp_en_dir(C, O);
    if (ACperp * AO > 0)
    {
        m_vertices.erase(m_vertices.begin() + 1);
        dir = ACperp;
        return false;
    }

    return true;
}