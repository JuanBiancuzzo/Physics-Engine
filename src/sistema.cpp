#include "sistema.h"

using namespace sistema;

template <typename T>
bool insertar_sin_repetir(std::vector<T> &lista, T elemento)
{
    for (T e : lista)
        if (e == elemento)
            return false;
    lista.emplace_back(elemento);
    return true;
}

Sistema::Sistema(std::vector<Particula *> &particulas)
{
    for (Particula *particula : particulas)
        insertar_sin_repetir<Particula *>(m_particulas, particula);
}

void Sistema::agregar_interaccion(Particula *particula, Particula *referencia, Vector2 &direccion)
{
    particula->agregar_interaccion(referencia, direccion);
}

void Sistema::expandir_fuerzas()
{
    for (Particula *particula : m_particulas)
        particula->expandir();
}

Particula::Particula(float masa, Vector2 velocidad, Vector2 fuerza)
    : m_velocidad(velocidad), m_fuerza(fuerza), m_masa(masa)
{
}

Particula::Particula(float masa)
    : m_masa(masa)
{
}

Particula::~Particula()
{
    for (Interaccion *interaccion : m_interacciones)
        delete interaccion;
}

void Particula::agregar_interaccion(Particula *referencia, Vector2 &direccion)
{
    Interaccion *interaccion = new Interaccion(referencia, direccion);
    insertar_sin_repetir<Interaccion *>(m_interacciones, interaccion);
}

void Particula::expandir()
{
    Vector2 resultante;
    do
    {
        Vector2 cant_movimiento = m_velocidad * m_masa;
        resultante *= .0f;

        for (Interaccion *interaccion : m_interacciones)
            resultante += interaccion->expandir(m_fuerza);

        m_fuerza += resultante;
        m_velocidad += (m_fuerza / m_masa) * m_dt;
    } while (!resultante.nulo());
}

Particula_estatica::Particula_estatica()
    : Particula(std::numeric_limits<float>::infinity())
{
}

void Particula_estatica::expandir()
{
}

Interaccion::Interaccion(Particula *particula, Vector2 &direccion)
    : m_particula(particula), m_direccion(direccion)
{
}

Vector2 Interaccion::expandir(Vector2 &fuerza)
{
    Vector2 fuerza_resultante = fuerza.proyeccion(m_direccion);

    Vector2 resultante;
    if (fuerza_resultante * m_direccion > 0)
        resultante += fuerza_resultante;

    if (!resultante.nulo())
    {
        m_particula->m_fuerza += resultante;
        m_particula->expandir();
    }

    return (resultante * -1.0f);
}
