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
    particula->agregar_interaccion({referencia, direccion});
}

void Sistema::expandir_interacciones(float dt)
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

    for (Particula *particula : m_particulas)
        particula->avanzar(dt);
}

Particula::Particula()
    : m_velocidad(Vector2()), m_fuerza(Vector2()), m_velocidad_angular(.0f), m_torque(.0f)
{
}

void Particula::agregar_interaccion(Interaccion interaccion)
{
    for (Interaccion interaccion_actual : m_interacciones)
        if (interaccion_actual.m_particula == interaccion.m_particula)
            return;
    m_interacciones.emplace_back(interaccion);
}

void Particula::agregar_atributo(Velocidad velocidad)
{
    m_velocidad += velocidad;
}

void Particula::agregar_atributo(Fuerza fuerza)
{
    m_fuerza += fuerza;
}

void Particula::agregar_atributo(VelocidadAngular velocidad_angular)
{
    m_velocidad_angular += velocidad_angular;
}

void Particula::agregar_atributo(Torque torque)
{
    m_torque += torque;
}

ParticulaDinamica::ParticulaDinamica(cr::InfoCuerpo *cuerpo)
    : m_cuerpo(cuerpo)
{
}

bool ParticulaDinamica::expandir()
{
    std::vector<Interactuar *> interactuables = {&m_fuerza, &m_velocidad, &m_velocidad_angular};
    bool resultado = true;

    for (Interaccion interaccion : m_interacciones)
        for (Interactuar *interactuable : interactuables)
            resultado &= interactuable->interactuar(this, interaccion);
    
    return resultado;
}

bool ParticulaDinamica::actualizar()
{
    return true;
}

void ParticulaDinamica::avanzar(float dt)
{
    std::vector<Avanzar *> actualizables = {&m_fuerza, &m_torque};

    for (Avanzar *actualizable : actualizables)
        actualizable->avanzar(this, dt);
}

ParticulaEstatica::ParticulaEstatica(cr::CuerpoRigido *cuerpo)
    : m_cuerpo(cuerpo)
{
}

bool ParticulaEstatica::expandir()
{
    return true;
}

bool ParticulaEstatica::actualizar()
{
    return true;
}

void ParticulaEstatica::avanzar(float dt)
{
}

// Particula::Particula(float masa, Vector2 velocidad, Vector2 fuerza, float coeficiente)
//     : m_velocidad(velocidad), m_fuerza(fuerza), m_masa(masa), m_coeficiente(coeficiente), m_estatica(false),
//       m_velocidad_guardada(velocidad), m_fuerza_guardada(fuerza)
// {
// }

// Particula::Particula()
//     : m_estatica(true)
// {
// }

// Particula::~Particula()
// {
//     for (Interaccion *interaccion : m_interacciones)
//         delete interaccion;
// }

// void Particula::agregar_interaccion(Particula *referencia, Vector2 &direccion)
// {
//     for (Interaccion *interaccion : m_interacciones)
//         if (interaccion->m_particula == referencia)
//             return;

//     m_interacciones.emplace_back(new Interaccion(referencia, direccion));
// }

// bool Particula::expandir()
// {
//     if (m_fuerza.nulo() && m_velocidad.nulo())
//         return true;

//     bool hay_interaccion = false;

//     for (Interaccion *interaccion : m_interacciones)
//         hay_interaccion |= interaccion->expandir(this);

//     return !hay_interaccion;
// }

// void Particula::agregar_al_historial(Particula *particula)
// {
//     m_historial.emplace_back(particula);
// }

// bool Particula::visitaste(Particula *particula)
// {
//     for (Particula *p : m_historial)
//         if (p == particula)
//             return true;
//     return false;
// }

// void Particula::actualizar()
// {
//     m_velocidad = m_velocidad_guardada;
//     m_fuerza = m_fuerza_guardada;
//     m_historial.clear();
// }

// void Particula::velocidad_por_choque(Vector2 fuerza_choque)
// {
//     if (!m_estatica)
//         m_velocidad_guardada += (fuerza_choque) / m_masa;
// }

// void Particula::aplicar_fuerza(Vector2 fuerza)
// {
//     if (!m_estatica)
//         m_fuerza_guardada += fuerza;
// }

// Interaccion::Interaccion(Particula *particula, Vector2 &direccion)
//     : m_particula(particula), m_direccion(direccion)
// {
// }

// Vector2 fuerza_de_choque(Particula *particula, Particula *referencia, Vector2 &direccion)
// {
//     float masa1 = particula->m_masa;
//     float masa2 = (referencia->m_estatica) ? masa1 : referencia->m_masa;

//     float coeficiente1 = particula->m_coeficiente;
//     float coeficiente2 = (referencia->m_estatica) ? coeficiente1 : referencia->m_coeficiente;

//     float coeficiente = (coeficiente1 + coeficiente2) / 4.0f + .5f;

//     Vector2 velocidad_de_choque = particula->m_velocidad.proyeccion(direccion) - referencia->m_velocidad.proyeccion(direccion);
//     float promedio_de_masas = (masa1 + masa2) / 2.0f;

//     Vector2 fuerza = (velocidad_de_choque * masa1 * masa2) / (promedio_de_masas);

//     return fuerza * coeficiente * (referencia->m_estatica ? 2.0f : 1.0f);
// }

// bool Interaccion::expandir(Particula *particula)
// {
//     if (m_particula->en_historial(particula))
//         return false;

//     Vector2 fuerza_resultante = particula->m_fuerza.proyeccion(m_direccion);
//     Vector2 fuerza_choque = fuerza_de_choque(particula, m_particula, m_direccion);

//     bool hay_resultante = fuerza_resultante * m_direccion > 0;
//     bool hay_choque = fuerza_choque * m_direccion > 0 && particula->m_velocidad * m_direccion > 0;

//     if (hay_choque)
//     {
//         m_particula->velocidad_por_choque(fuerza_choque);
//         particula->velocidad_por_choque(fuerza_choque * -1.0f);
//     }

//     if (hay_resultante)
//     {
//         m_particula->aplicar_fuerza(fuerza_resultante);
//         particula->aplicar_fuerza(fuerza_resultante * -1.0f);
//     }

//     if (hay_resultante || hay_choque)
//         particula->agregar_elemento(m_particula);

//     return hay_resultante || hay_choque;
// }
