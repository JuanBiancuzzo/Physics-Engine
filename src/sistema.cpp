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

void Sistema::expandir_interacciones()
{
    bool terminado = false;
    for (int i = 0; i < 10 && !terminado; i++)
    {
        terminado = true;
        for (Particula *particula : m_particulas)
            terminado &= particula->expandir();

        for (Particula *particula : m_particulas)
            particula->actualizar_propiedades();
    }

    for (Particula *particula : m_particulas)
        particula->actualizar(m_dt);
}

Particula::Particula(float masa, Vector2 velocidad, Vector2 fuerza, float coeficiente)
    : m_velocidad(velocidad), m_fuerza(fuerza), m_masa(masa), m_coeficiente(coeficiente), m_estatica(false),
      m_velocidad_guardada(velocidad), m_fuerza_guardada(fuerza)
{
}

Particula::Particula()
    : m_estatica(true)
{
}

Particula::~Particula()
{
    for (Interaccion *interaccion : m_interacciones)
        delete interaccion;
}

void Particula::agregar_interaccion(Particula *referencia, Vector2 &direccion, float dt)
{
    for (Interaccion *interaccion : m_interacciones)
        if (interaccion->m_particula == referencia)
            return;

    Interaccion *interaccion = new Interaccion(referencia, direccion, dt);
    m_interacciones.emplace_back(interaccion);
}

bool Particula::expandir()
{
    if (m_fuerza.nulo() && m_velocidad.nulo())
        return true;

    bool hay_interaccion = false;

    for (Interaccion *interaccion : m_interacciones)
        hay_interaccion |= interaccion->expandir(this);

    return !hay_interaccion;
}

void Particula::agregar_al_historial(Particula *particula)
{
    m_historial.emplace_back(particula);
}

bool Particula::visitaste(Particula *particula)
{
    for (Particula *p : m_historial)
        if (p == particula)
            return true;
    return false;
}

void Particula::actualizar(float dt)
{
    if (!m_estatica)
        m_velocidad += (m_fuerza * dt) / m_masa;
    m_fuerza *= .0f;
}

void Particula::actualizar_propiedades()
{
    m_velocidad = m_velocidad_guardada;
    m_fuerza = m_fuerza_guardada;
    m_historial.clear();
}

void Particula::velocidad_por_choque(Vector2 fuerza_choque)
{
    if (!m_estatica)
        m_velocidad_guardada += (fuerza_choque) / m_masa;
}

void Particula::aplicar_fuerza(Vector2 fuerza)
{
    if (!m_estatica)
        m_fuerza_guardada += fuerza;
}

Interaccion::Interaccion(Particula *particula, Vector2 &direccion, float dt)
    : m_particula(particula), m_direccion(direccion), m_dt(dt)
{
}

Vector2 fuerza_de_choque(Particula *particula, Particula *referencia, Vector2 &direccion)
{
    float masa1 = particula->m_masa;
    float masa2 = (referencia->m_estatica) ? masa1 : referencia->m_masa;

    float coeficiente1 = particula->m_coeficiente;
    float coeficiente2 = (referencia->m_estatica) ? coeficiente1 : referencia->m_coeficiente;

    float coeficiente = (coeficiente1 + coeficiente2) / 4.0f + .5f;

    Vector2 velocidad_de_choque = particula->m_velocidad.proyeccion(direccion) - referencia->m_velocidad.proyeccion(direccion);
    float promedio_de_masas = (masa1 + masa2) / 2.0f;

    Vector2 fuerza = (velocidad_de_choque * masa1 * masa2) / (promedio_de_masas);

    return fuerza * coeficiente * (referencia->m_estatica ? 2.0f : 1.0f);
}

bool Interaccion::expandir(Particula *particula)
{
    if (m_particula->visitaste(particula))
        return false;

    Vector2 fuerza_resultante = particula->m_fuerza.proyeccion(m_direccion);
    Vector2 fuerza_choque = fuerza_de_choque(particula, m_particula, m_direccion);

    bool hay_resultante = fuerza_resultante * m_direccion > 0;
    bool hay_choque = fuerza_choque * m_direccion > 0 && particula->m_velocidad * m_direccion > 0;

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

    if (hay_resultante || hay_choque)
        particula->agregar_al_historial(m_particula);

    return hay_resultante || hay_choque;
}
