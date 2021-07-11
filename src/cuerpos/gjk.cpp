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
    while (vertice * dir > 0)
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
    return m_cuerpo1->punto_soporte(dir) - m_cuerpo2->punto_soporte(dir * -1.0f);
}

Simplex::Simplex(Vector2 primer_vertice)
    : m_vertices({primer_vertice, Vector2(), Vector2()}), m_cantidad(0)
{
}

void Simplex::agregar_vertice(Vector2 &vertice)
{
    m_vertices = {vertice, m_vertices[0], m_vertices[1]};
    m_cantidad = std::min(m_cantidad + 1, 3u);
}

bool Simplex::contiene_origen(Vector2 &direccion)
{
    if (m_cantidad == 2)
        return caso_linea(direccion);
    return caso_triangulo(direccion);
}

Simplex &Simplex::operator=(std::initializer_list<Vector2> lista)
{
    for (auto v = lista.begin(); v != lista.end(); v++)
        m_vertices[std::distance(lista.begin(), v)] = *v;

    m_cantidad = lista.size();
    return *this;
}

bool en_rango(float valor, float valor_esperado)
{
    float dv = .1f;
    return (valor_esperado - dv < valor && valor < valor_esperado + dv);
}

bool Simplex::caso_linea(Vector2 &direccion)
{
    Vector2 a = m_vertices[0];
    Vector2 b = m_vertices[1];
    Vector2 origen = Vector2();

    Vector2 ab = b - a;
    Vector2 ao = origen - a;

    Vector2 ab_perp = a.perp_en_dir(b, origen);

    if (en_rango(ab_perp * ao, .0f))
        return true;

    direccion = ab_perp;
    return false;
}

bool Simplex::caso_triangulo(Vector2 &direccion)
{
    Vector2 a = m_vertices[0];
    Vector2 b = m_vertices[1];
    Vector2 c = m_vertices[2];
    Vector2 origen = Vector2();

    Vector2 ab = b - a;
    Vector2 ac = a - c;
    Vector2 ao = origen - a;

    Vector2 ab_perp = a.perp_en_dir(b, origen);
    Vector2 ac_perp = a.perp_en_dir(c, origen);

    if (ab_perp * ao > 0)
    {
        *this = {a, b};
        return caso_linea(direccion);
    }

    if (ac_perp * ao > 0)
    {
        *this = {a, c};
        return caso_linea(direccion);
    }
    return true;
}