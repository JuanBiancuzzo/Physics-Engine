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

Sistema::Sistema(std::vector<Particula *> &particulas, float dt)
    : m_dt(dt)
{
    for (Particula *particula : particulas)
        insertar_sin_repetir<Particula *>(m_particulas, particula);
}

void Sistema::agregar_interaccion(Particula *particula, Particula *referencia, Vector2 &direccion)
{
    particula->agregar_interaccion(referencia, direccion, m_dt);
}

void Sistema::expandir_fuerzas()
{
    for (Particula *particula : m_particulas)
        particula->expandir();
}

Particula::Particula(float masa, Vector2 velocidad, Vector2 fuerza)
    : m_velocidad(velocidad), m_fuerza(fuerza), m_masa(masa), m_estatica(false)
{
}

Particula::Particula()
    : m_masa(.0f), m_estatica(true)
{
}

Particula::~Particula()
{
    for (Interaccion *interaccion : m_interacciones)
        delete interaccion;
}

void Particula::agregar_interaccion(Particula *referencia, Vector2 &direccion, float dt)
{
    Interaccion *interaccion = new Interaccion(referencia, direccion, dt);
    insertar_sin_repetir<Interaccion *>(m_interacciones, interaccion);
}

void Particula::expandir()
{
    if (m_estatica)
        return;

    Vector2 resultante;
    do
    {
        resultante *= .0f;

        for (Interaccion *interaccion : m_interacciones)
            resultante += interaccion->expandir(this);

    } while (!resultante.nulo());
}

void Particula::actualizar(Vector2 direccion, float dt)
{
    Vector2 fuerza = m_fuerza.proyeccion(direccion);

    if (!m_estatica)
        m_velocidad += (fuerza * dt) / m_masa;
    m_fuerza -= fuerza;
}

Interaccion::Interaccion(Particula *particula, Vector2 &direccion, float dt)
    : m_particula(particula), m_direccion(direccion), m_dt(dt)
{
}

Vector2 fuerza_de_choque(Particula *particula, Particula *referencia, Vector2 &direccion, float dt)
{
    float masa1 = particula->m_masa;
    float masa2 = referencia->m_masa;

    if (referencia->m_estatica)
        masa2 = masa1;

    Vector2 velocidad_de_choque = particula->m_velocidad.proyeccion(direccion) - referencia->m_velocidad.proyeccion(direccion);
    float promedio_de_masas = (masa1 + masa2) / 2;

    return ((velocidad_de_choque * masa1 * masa2) / (promedio_de_masas * dt));
}

Vector2 Interaccion::expandir(Particula *particula)
{
    Vector2 fuerza_resultante = particula->m_fuerza.proyeccion(m_direccion);
    Vector2 fuerza_choque = fuerza_de_choque(particula, m_particula, m_direccion, m_dt);

    Vector2 resultante;

    if (fuerza_resultante * m_direccion > 0)
        resultante += fuerza_resultante;

    if (fuerza_choque * m_direccion > 0)
        resultante += fuerza_choque;

    if (resultante.nulo())
        return Vector2();

    m_particula->m_fuerza += resultante;
    particula->m_fuerza -= resultante;

    m_particula->actualizar(m_direccion, m_dt);
    particula->actualizar(m_direccion, m_dt);

    m_particula->expandir();
    return (resultante * -1.0f);
}
