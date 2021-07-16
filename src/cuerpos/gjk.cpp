#include "gjk.h"

Gjk::Gjk(CuerpoRigido *cuerpo1, CuerpoRigido *cuerpo2)
    : m_cuerpo1(cuerpo1), m_cuerpo2(cuerpo2)
{
}

bool Gjk::colisionan()
{
    Vector2 direccion = (m_cuerpo2->m_posicion - m_cuerpo1->m_posicion).normal();
    Vector2 punto_soporte = soporte(direccion);
    Simplex simplex(punto_soporte);
    direccion = punto_soporte * -1.0f; // vector direccion del punto hasta el origen

    while (true)
    {
        punto_soporte = soporte(direccion);
        if (punto_soporte * direccion < 0)
            return false;
        simplex.agregar_vertice(punto_soporte);
        if (simplex.contiene_origen(direccion))
            return true;
    }
}

Vector2 Gjk::soporte(Vector2 &direccion)
{
    Vector2 opuesta = direccion * -1.0f;
    return m_cuerpo1->punto_soporte(direccion) - m_cuerpo2->punto_soporte(opuesta);
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
    switch (m_cantidad)
    {
    case 2:
        return caso_linea(direccion);
        break;
    case 3:
        return caso_triangulo(direccion);
        break;
    }
    // nunca se tendria que llegar aca
    return false;
}

Simplex &Simplex::operator=(std::initializer_list<Vector2> lista)
{
    for (auto vertice = lista.begin(); vertice != lista.end(); vertice++)
        m_vertices[std::distance(lista.begin(), vertice)] = *vertice;

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

    Vector3 abc = ab.vectorial(ac);

    if (abc.vectorial(ac) * ao > 0)
    {
        if (ac * ao > 0)
        {
            *this = {a.dos_dimensiones(), c.dos_dimensiones()};
            direccion = (ac.vectorial(ao).vectorial(ac)).dos_dimensiones();
        }
        else
        {
            *this = {a.dos_dimensiones(), b.dos_dimensiones()};
            return caso_linea(direccion);
        }
    }
    else
    {
        if (ab.vectorial(abc) * ao > 0)
        {
            *this = {a.dos_dimensiones(), b.dos_dimensiones()};
            return caso_linea(direccion);
        }
        else
        {
            if (abc * ao > 0)
            {
                direccion = abc.dos_dimensiones();
            }
            else
            {
                *this = {a.dos_dimensiones(), b.dos_dimensiones(), c.dos_dimensiones()};
                direccion = (abc * -1.0f).dos_dimensiones();
            }
        }
    }

    return true;
}