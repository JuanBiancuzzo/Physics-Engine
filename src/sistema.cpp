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
        particula->expandir(m_dt);
}

Particula::Particula(float masa, Vector2 velocidad, Vector2 fuerza)
    : m_velocidad(velocidad), m_fuerza(fuerza), m_masa(masa), m_estatica(false)
{
}

Particula::Particula()
    : m_masa(1.0f), m_estatica(true)
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

void Particula::expandir(float dt)
{
    if (m_estatica)
        return;

    Vector2 resultante;
    do
    {
        resultante *= .0f;

        for (Interaccion *interaccion : m_interacciones)
            resultante += interaccion->expandir(m_fuerza, m_masa, m_velocidad);

        m_fuerza += resultante;
        actualizar(dt);

    } while (!resultante.nulo());
}

void Particula::actualizar(float dt)
{
    if (!m_estatica)
        m_velocidad += m_fuerza / m_masa;
    else
        m_velocidad *= .0f;
}

Interaccion::Interaccion(Particula *particula, Vector2 &direccion, float dt)
    : m_particula(particula), m_direccion(direccion), m_dt(dt)
{
}

Vector2 fuerza_de_choque(Vector2 &velocidad_de_choque, float masa1, float masa2, float dt)
{
    return ((velocidad_de_choque * masa1 * masa1) / ((masa1 + masa2) * dt));
}

Vector2 Interaccion::expandir(Vector2 &fuerza, float masa, Vector2 &velocidad)
{
    Vector2 fuerza_resultante = fuerza.proyeccion(m_direccion);
    Vector2 velocidad_de_choque = velocidad.proyeccion(m_direccion) - m_particula->m_velocidad.proyeccion(m_direccion);
    Vector2 resultante(.0f, .0f);

    if (!velocidad_de_choque.nulo() && !m_particula->m_estatica)
        resultante += fuerza_de_choque(velocidad_de_choque, masa, m_particula->m_masa, m_dt);

    if (fuerza_resultante * m_direccion > 0)
        resultante += fuerza_resultante;

    std::cout << "Resultante: " << resultante.x << ", " << resultante.y << std::endl;

    if (resultante.nulo())
        return Vector2();

    m_particula->m_fuerza += fuerza_resultante;
    m_particula->actualizar(m_dt);
    m_particula->expandir(m_dt); // aca se crea un loop infinito
    return (resultante * -1.0f);
}

// Vector2 Interaccion::expandir_velocidad(float masa, Vector2 &velocidad)
// {
//     Vector2 velocidad_de_choque = velocidad.proyeccion(m_direccion) - m_particula->m_velocidad.proyeccion(m_direccion);
//     Vector2 fuerza_de_choque;

//     if (!velocidad_de_choque.nulo() && !m_particula->m_estatica)
//         fuerza_de_choque += (velocidad_de_choque * masa * masa) / (masa + m_particula->m_masa);

//     if (fuerza_de_choque * m_direccion <= 0)
//         return Vector2();

//     m_particula->m_velocidad += (fuerza_de_choque / m_particula->m_masa);
//     m_particula->expandir_velocidad();
//     return (fuerza_de_choque * -1.0f);
// }
