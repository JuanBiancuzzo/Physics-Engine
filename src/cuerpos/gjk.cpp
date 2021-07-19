#include "gjk.h"

using namespace cr;

Gjk::Gjk(CuerpoRigido *cuerpo1, CuerpoRigido *cuerpo2)
    : m_cuerpo1(cuerpo1), m_cuerpo2(cuerpo2)
{
}

bool Gjk::colisionan()
{
    Simplex simplex;
    return colisionan(simplex);
}

bool Gjk::colisionan(Simplex &simplex)
{
    Vector2 direccion = Vector2(1.0f, .0f);
    Vector2 punto_soporte = soporte(direccion);
    simplex.agregar_vertice(punto_soporte);
    direccion = punto_soporte * -1.0f;

    while (true)
    {
        punto_soporte = soporte(direccion);

        if (punto_soporte * direccion < 0)
            return false;

        simplex.agregar_vertice(punto_soporte);
        if (simplex.contiene_origen(direccion))
            return true;
    }
    return false;
}

cr::PuntoDeColision Gjk::info_colision()
{ // buscar errores
    Simplex simplex;
    bool resultado = colisionan(simplex);
    Polytope polytope(simplex.inicio(), simplex.fin());

    int minIndex = 0;
    float minDistance = std::numeric_limits<float>::max();
    Vector2 minNormal;

    while (minDistance == std::numeric_limits<float>::max())
    {
        for (int i = 0; i < polytope.cantidad(); i++)
        {
            int j = (i + 1) % polytope.cantidad();

            Vector2 ij = polytope[j] - polytope[i];
            Vector2 normal = ij.perpendicular().normal();

            if (normal * polytope[i] < 0)
                normal *= -1.0f;

            if (normal * polytope[i] < minDistance)
            {
                minDistance = normal * polytope[i];
                minNormal = normal;
                minIndex = j;
            }
        }

        Vector2 punto_soporte = soporte(minNormal);
        float sDistance = minNormal * punto_soporte;

        if (std::abs(sDistance - minDistance) > .001f)
        {
            minDistance = std::numeric_limits<float>::max();
            polytope.insertar(minIndex, punto_soporte);
        }
    }

    return {m_cuerpo1->punto_soporte(minNormal), minNormal, resultado};
}

Vector2 Gjk::soporte(Vector2 &direccion)
{
    Vector2 opuesta = direccion * -1.0f;
    return m_cuerpo1->punto_soporte(direccion) - m_cuerpo2->punto_soporte(opuesta);
}

Simplex::Simplex()
    : m_vertices({Vector2(), Vector2(), Vector2()}), m_cantidad(0)
{
}

void Simplex::agregar_vertice(Vector2 &vertice)
{
    m_vertices = {vertice, m_vertices[0], m_vertices[1]};
    m_cantidad = std::min(m_cantidad + 1, 3);
}

bool Simplex::contiene_origen(Vector2 &direccion)
{
    if (m_cantidad == 2)
        return caso_linea(direccion);
    return caso_triangulo(direccion);
}

Simplex &Simplex::operator=(std::initializer_list<Vector2> lista)
{
    for (auto vertice = lista.begin(); vertice != lista.end(); vertice++)
        m_vertices[std::distance(lista.begin(), vertice)] = *vertice;

    m_cantidad = lista.size();
    return *this;
}

std::array<Vector2, 3>::const_iterator Simplex::inicio() const
{
    return m_vertices.begin();
}

std::array<Vector2, 3>::const_iterator Simplex::fin() const
{
    return m_vertices.end() - (3 - m_cantidad);
}

bool Simplex::caso_linea(Vector2 &direccion)
{
    Vector3 a, b;
    a = m_vertices[0];
    b = m_vertices[1];
    Vector3 origen;

    Vector3 ab = b - a;
    Vector3 ao = origen - a;

    direccion = (ab.vectorial(ao).vectorial(ab)).dos_dimensiones();

    return false;
}

bool Simplex::caso_triangulo(Vector2 &direccion)
{
    Vector3 a, b, c;
    a = m_vertices[0];
    b = m_vertices[1];
    c = m_vertices[2];
    Vector3 origen;

    Vector3 ab = b - a;
    Vector3 ac = c - a;
    Vector3 ao = origen - a;

    Vector3 ab_perp = (ac.vectorial(ab)).vectorial(ab);
    if (ab_perp * ao > 0)
    {
        *this = {a.dos_dimensiones(), b.dos_dimensiones()};
        direccion = ab_perp.dos_dimensiones();
        return false;
    }

    Vector3 ac_perp = (ab.vectorial(ac)).vectorial(ac);
    if (ac_perp * ao > 0)
    {
        *this = {a.dos_dimensiones(), c.dos_dimensiones()};
        direccion = ac_perp.dos_dimensiones();
        return false;
    }

    return true;
}

Polytope::Polytope(auto inicio, auto fin)
    : m_vertices(inicio, fin)
{
}

int Polytope::cantidad()
{
    return m_vertices.size();
}

Vector2 &Polytope::operator[](int i)
{
    return m_vertices[i];
}

void Polytope::insertar(int posicion, Vector2 &vertice)
{
    m_vertices.insert(m_vertices.begin() + posicion, vertice);
}