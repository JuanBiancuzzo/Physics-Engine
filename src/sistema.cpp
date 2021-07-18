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

Sistema::Sistema(std::vector<Particula *> particulas)
    : m_particulas(particulas)
{
}

void Sistema::agregar_interaccion(Particula *particula, Particula *referencia, Vector2 &direccion)
{
    Vector2 punto_aplicacion = particula->m_cuerpo->punto_soporte(direccion);
    particula->agregar_interaccion(referencia, direccion, punto_aplicacion);
}

void Sistema::agregar_interaccion(Particula *particula, Particula *referencia)
{
    cr::PuntoDeColision pc;
    if (!referencia->interactua(particula, pc.normal, pc.punto_aplicacion))
        pc = particula->m_cuerpo->punto_de_colision(referencia->m_cuerpo);
    particula->agregar_interaccion(referencia, pc.normal, pc.punto_aplicacion);
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
            particula->actualizar();
    }
}

Particula::Particula(cr::CuerpoRigido *cuerpo, Vector2 velocidad, Vector2 fuerza, float coeficiente)
    : m_cuerpo(cuerpo), m_velocidad(velocidad), m_fuerza(fuerza), m_coeficiente(coeficiente),
      m_velocidad_guardada(velocidad), m_fuerza_guardada(fuerza)
{
}

Particula::~Particula()
{
    for (Interaccion *interaccion : m_interacciones)
        delete interaccion;
}

void Particula::agregar_interaccion(Particula *referencia, Vector2 &normal, Vector2 &punto_aplicacion)
{
    for (Interaccion *interaccion : m_interacciones)
        if (interaccion->m_particula == referencia)
            return;

    m_interacciones.emplace_back(new Interaccion(referencia, normal, punto_aplicacion));
}

void Particula::agregar_al_historial(Particula *particula)
{
    m_historial.emplace_back(particula);
}

bool Particula::interactua(Particula *referencia, Vector2 &normal, Vector2 &punto_aplicacion)
{
    for (Interaccion *interaccion : m_interacciones)
        if (interaccion->m_particula == referencia)
        {
            normal = interaccion->m_normal * -1.0f;
            punto_aplicacion = interaccion->m_punto_aplicacion;
            return true;
        }
    return false;
}

bool Particula::visitaste(Particula *particula)
{
    for (Particula *p : m_historial)
        if (p == particula)
            return true;
    return false;
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

void Particula::actualizar()
{
    m_velocidad = m_velocidad_guardada;
    m_fuerza = m_fuerza_guardada;
    m_historial.clear();
}

void Particula::velocidad_por_choque(Vector2 fuerza_choque)
{
    m_velocidad_guardada += (fuerza_choque) / m_cuerpo->m_masa;
}

void Particula::aplicar_fuerza(Vector2 punto_aplicacion, Vector2 fuerza)
{
    m_fuerza_guardada += fuerza;
    m_torque += (punto_aplicacion - m_cuerpo->m_posicion).vectorial(fuerza);
}

ParticulaEstatica::ParticulaEstatica(cr::CuerpoRigido *cuerpo)
    : Particula(cuerpo, Vector2(), Vector2(), -1.0f)
{
}

bool ParticulaEstatica::expandir()
{
    return true;
}

void ParticulaEstatica::actualizar()
{
    m_historial.clear();
}

void ParticulaEstatica::velocidad_por_choque(Vector2 fuerza_choque)
{
}

void ParticulaEstatica::aplicar_fuerza(Vector2 punto_aplicacion, Vector2 fuerza)
{
}

Interaccion::Interaccion(Particula *particula, Vector2 &normal, Vector2 &punto_aplicacion)
    : m_particula(particula), m_normal(normal), m_punto_aplicacion(punto_aplicacion)
{
}

Vector2 fuerza_de_choque(Particula *particula, Particula *referencia, Vector2 &direccion)
{
    float masa1 = particula->m_cuerpo->m_masa;
    float masa2 = (referencia->m_cuerpo->m_masa < 0) ? masa1 : referencia->m_cuerpo->m_masa;

    float coeficiente1 = particula->m_coeficiente;
    float coeficiente2 = (referencia->m_coeficiente < 0) ? coeficiente1 : referencia->m_coeficiente;

    float coeficiente = (coeficiente1 + coeficiente2) / 4.0f + .5f;

    Vector2 velocidad_de_choque = particula->m_velocidad.proyeccion(direccion) - referencia->m_velocidad.proyeccion(direccion);
    float promedio_de_masas = (masa1 + masa2) / 2.0f;

    Vector2 fuerza = (velocidad_de_choque * masa1 * masa2) / (promedio_de_masas);

    return fuerza * coeficiente * (referencia->m_cuerpo->m_masa < 0 ? 2.0f : 1.0f);
}

bool Interaccion::expandir(Particula *particula)
{
    if (m_particula->visitaste(particula))
        return false;

    Vector2 fuerza_resultante = particula->m_fuerza.proyeccion(m_normal);
    Vector2 fuerza_choque = fuerza_de_choque(particula, m_particula, m_normal);

    bool hay_resultante = fuerza_resultante * m_normal > 0;
    bool hay_choque = fuerza_choque * m_normal > 0 && particula->m_velocidad * m_normal > 0;

    if (hay_choque)
    {
        m_particula->velocidad_por_choque(fuerza_choque);
        particula->velocidad_por_choque(fuerza_choque * -1.0f);
    }

    if (hay_resultante)
    {
        m_particula->aplicar_fuerza(m_punto_aplicacion, fuerza_resultante);
        particula->aplicar_fuerza(m_punto_aplicacion, fuerza_resultante * -1.0f);
    }

    if (hay_resultante || hay_choque)
        particula->agregar_al_historial(m_particula);

    return hay_resultante || hay_choque;
}
