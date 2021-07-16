#include "gjk.h"

Gjk::Gjk(CuerpoRigido *cuerpo1, CuerpoRigido *cuerpo2)
    : m_cuerpo1(cuerpo1), m_cuerpo2(cuerpo2)
{
}

bool Gjk::colisionan()
{
    Vector2 direccion = (m_cuerpo2->m_posicion - m_cuerpo1->m_posicion).normal();
    Simplex simplex(soporte(direccion));
    direccion *= -1.0f; // vector direccion del punto hasta el origen

    while (true)
    {
        Vector2 a = soporte(direccion);
        if (a * direccion < 0)
            return false;
        simplex.agregar_vertice(a);
        if (simplex.contiene_origen(direccion))
            return true;
    }
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
    Vector3 a, b, origen;
    a = m_vertices[0];
    b = m_vertices[1];
    origen = Vector2();

    Vector3 ab = b - a;
    Vector3 ao = origen - a;

    direccion = ((ab.vectorial(ao)).vectorial(ab)).dos_dimensiones();
    return false;
}

bool Simplex::caso_triangulo(Vector2 &direccion)
{
    Vector3 a, b, c, origen;
    a = m_vertices[0];
    b = m_vertices[1];
    c = m_vertices[2];
    origen = Vector2();

    Vector3 ab = b - a;
    Vector3 ac = a - c;
    Vector3 ao = origen - a;

    Vector3 ab_perp = (ac.vectorial(ab)).vectorial(ab);

    if (ab_perp * ao > 0)
    {
        *this = {a.dos_dimensiones(), b.dos_dimensiones()};
        return caso_linea(direccion);
    }

    Vector3 ac_perp = (ab.vectorial(ac)).vectorial(ac);

    if (ac_perp * ao > 0)
    {
        *this = {a.dos_dimensiones(), c.dos_dimensiones()};
        return caso_linea(direccion);
    }
    return true;
}