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

std::vector<Particula *> Sistema::primeras_particulas()
{
    std::vector<Particula *> primeros;
    return primeros;
}

void Sistema::expandir_fuerzas()
{
    for (Particula *particula : primeras_particulas())
        particula->expandir();
}

Particula::Particula(Vector2 &fuerza)
    : m_fuerza(fuerza)
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
    while (resultante != (resultante * .0f))
    {
        resultante *= .0f;
        for (Interaccion *interaccion : m_interacciones)
            resultante += interaccion->expandir(m_fuerza);
        m_fuerza += resultante;
    }
}

Interaccion::Interaccion(Particula *particula, Vector2 &direccion)
    : m_particula(particula), m_direccion(direccion)
{
}

Vector2 Interaccion::expandir(Vector2 &fuerza)
{
    Vector2 proyeccion = fuerza.proyeccion(m_direccion);
    if (proyeccion * m_direccion <= 0)
        return Vector2();

    m_particula->m_fuerza += proyeccion;
    m_particula->expandir();
    return (proyeccion * -1.0f);
}
