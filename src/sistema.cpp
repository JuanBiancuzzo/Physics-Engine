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
    bool terminado = false;
    while (!terminado)
    {
        terminado = true;
        for (Particula *particula : m_particulas)
            terminado &= particula->expandir();
    }

    for (Particula *particula : m_particulas)
        particula->actualizar(m_dt);
}

Particula::Particula(float masa, Vector2 velocidad, Vector2 fuerza)
    : m_velocidad(velocidad), m_fuerza(fuerza), m_masa(masa), m_coeficiente(1.0f), m_estatica(false)
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
    m_interacciones.emplace_back(interaccion);
}

bool Particula::expandir()
{
    if (m_fuerza.nulo() && m_velocidad.nulo())
        return true;

    bool hay_interaccion = false;

    Vector2 fuerza = m_fuerza;
    Vector2 velocidad = m_velocidad;

    for (Interaccion *interaccion : m_interacciones)
        hay_interaccion |= interaccion->expandir(this, fuerza, velocidad);

    return !hay_interaccion;
}

void Particula::actualizar(float dt)
{
    if (!m_estatica)
        m_velocidad += (m_fuerza * dt) / m_masa;
    m_fuerza *= .0f;
}

void Particula::velocidad_por_choque(Vector2 fuerza_choque)
{
    if (!m_estatica)
        m_velocidad += (fuerza_choque) / m_masa;
}

void Particula::aplicar_fuerza(Vector2 fuerza)
{
    if (!m_estatica)
        m_fuerza += fuerza;
}

Interaccion::Interaccion(Particula *particula, Vector2 &direccion, float dt)
    : m_particula(particula), m_direccion(direccion), m_dt(dt)
{
}

Vector2 fuerza_de_choque(Particula *particula, Vector2 &velocidad, Particula *referencia, Vector2 &direccion)
{
    float masa1 = particula->m_masa;
    float masa2 = referencia->m_masa;

    if (referencia->m_estatica)
        masa2 = masa1;

    Vector2 velocidad_de_choque = velocidad.proyeccion(direccion) - referencia->m_velocidad.proyeccion(direccion);
    float promedio_de_masas = (masa1 + masa2) / 2.0f;

    Vector2 fuerza = (velocidad_de_choque * masa1 * masa2) / (promedio_de_masas);

    return fuerza * (referencia->m_estatica ? 1.0f + particula->m_coeficiente : 1.0f);
}

bool Interaccion::expandir(Particula *particula, Vector2 &fuerza, Vector2 &velocidad)
{
    Vector2 fuerza_resultante = fuerza.proyeccion(m_direccion);
    Vector2 fuerza_choque = fuerza_de_choque(particula, velocidad, m_particula, m_direccion);

    bool hay_resultante = fuerza_resultante * m_direccion > 0;
    bool hay_choque = fuerza_choque * m_direccion > 0 && velocidad * m_direccion > 0;

    if (hay_choque)
    {
        m_particula->velocidad_por_choque(fuerza_choque);
        particula->velocidad_por_choque(fuerza_choque * -1.0f);
    }

    if (hay_resultante)
    {
        m_particula->aplicar_fuerza(fuerza_resultante);
        particula->aplicar_fuerza(fuerza_resultante * -1.0f);
    }

    return hay_resultante || hay_choque;
}
