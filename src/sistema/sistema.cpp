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

InfoCuerpo::InfoCuerpo(cr::CuerpoRigido *_cuerpo, float _masa, float _coeficiente)
    : cuerpo(_cuerpo), masa(_masa), inercia(_cuerpo->calcular_inercia(_masa)), coeficiente(_coeficiente)
{
}

Sistema::Sistema(std::vector<Particula *> particulas)
    : m_particulas(particulas)
{
}

void Sistema::agregar_interaccion(Particula *particula, Particula *referencia, Vector2 &direccion)
{
    atributo::Interaccion interaccion = {referencia, direccion};

    particula->agregar_interaccion(interaccion);
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

void Particula::agregar_interaccion(atributo::Interaccion interaccion)
{
    for (atributo::Interaccion interaccion_actual : m_interacciones)
        if (interaccion_actual.m_particula == interaccion.m_particula)
            return;
    m_interacciones.emplace_back(interaccion);
}

void Particula::agregar_atributo(atributo::Velocidad velocidad)
{
    m_velocidad += velocidad;
}

void Particula::agregar_atributo(atributo::Fuerza fuerza)
{
    m_fuerza += fuerza;
}

void Particula::agregar_atributo(atributo::VelocidadAngular velocidad_angular)
{
    m_velocidad_angular += velocidad_angular;
}

void Particula::agregar_atributo(atributo::Torque torque)
{
    m_torque += torque;
}

ParticulaDinamica::ParticulaDinamica(InfoCuerpo *cuerpo)
    : m_cuerpo(cuerpo)
{
}

bool ParticulaDinamica::expandir()
{
    std::vector<atributo::Interactuar *> interactuables = {&m_fuerza, &m_velocidad, &m_velocidad_angular};
    bool resultado = true;

    for (atributo::Interaccion interaccion : m_interacciones){
        for (atributo::Interactuar *interactuable : interactuables)
            resultado &= interactuable->interactuar(this, interaccion);
        agregar_elemento(interaccion.m_particula);   
    }
    return resultado;
}

void ParticulaDinamica::actualizar()
{
    std::vector<atributo::Atributo *> atributos = {&m_fuerza, &m_velocidad, &m_torque, &m_velocidad_angular};

    for (atributo::Atributo *atributo : atributos)
        atributo->actualizar();
    resetear();
}

void ParticulaDinamica::avanzar(float dt)
{
    std::vector<atributo::Avanzar *> actualizables = {&m_fuerza, &m_torque};

    for (atributo::Avanzar *actualizable : actualizables)
        actualizable->avanzar(this, dt);
}

float ParticulaDinamica::masa(float segunda_opcion)
{
    return m_cuerpo->masa;
}

float ParticulaDinamica::coeficiente(float segunda_opcion)
{
    return m_cuerpo->coeficiente;
}

bool ParticulaDinamica::refleja_fuerza()
{
    return false;
}

ParticulaEstatica::ParticulaEstatica(cr::CuerpoRigido *cuerpo)
    : m_cuerpo(cuerpo)
{
}

bool ParticulaEstatica::expandir()
{
    return true;
}

void ParticulaEstatica::actualizar()
{
    resetear();
}

void ParticulaEstatica::avanzar(float dt)
{
}

float ParticulaEstatica::masa(float segunda_opcion)
{
    return segunda_opcion;
}

float ParticulaEstatica::coeficiente(float segunda_opcion)
{
    return segunda_opcion;
}

bool ParticulaEstatica::refleja_fuerza()
{
    return true;
}

atributo::Fuerza::Fuerza(Vector2 magnitud = Vector2())
    : m_magnitud(magnitud)
{
}

void atributo::Fuerza::actualizar()
{
}

bool atributo::Fuerza::interactuar(ParticulaDinamica *referencia, Interaccion interaccion)
{
    if (referencia->en_historial(interaccion.m_particula))
        return false;

    Vector2 fuerza_resultante = referencia->m_fuerza.m_magnitud.proyeccion(interaccion.m_direccion);
    if (!(fuerza_resultante * interaccion.m_direccion))
        return false;
    
    referencia->m_fuerza += (fuerza_resultante * -1.0f);
    interaccion.m_particula->m_fuerza += fuerza_resultante;

    return true;
}

void atributo::Fuerza::avanzar(ParticulaDinamica *referencia, float dt)
{
    Vector2 resultado = (m_magnitud * dt) / referencia->m_cuerpo->masa;
    referencia->m_velocidad.m_magnitud += resultado;
}

void atributo::Fuerza::operator+=(atributo::Fuerza otro)
{
    m_magnitud += otro.m_magnitud;
}

Vector2 fuerza_de_choque(ParticulaDinamica *particula, Particula *referencia, Vector2 &direccion)
{
    float masa1 = particula->masa(.0f);
    float masa2 = referencia->masa(masa1);

    float coeficiente1 = particula->coeficiente(.0f);
    float coeficiente2 = referencia->coeficiente(coeficiente1);

    float coeficiente = (coeficiente1 + coeficiente2) / 4.0f + .5f;

    Vector2 velocidad_de_choque = particula->m_velocidad.m_magnitud.proyeccion(direccion) - referencia->m_velocidad.m_magnitud.proyeccion(direccion);
    float promedio_de_masas = (masa1 + masa2) / 2.0f;

    Vector2 fuerza = (velocidad_de_choque * masa1 * masa2) / (promedio_de_masas);

    return fuerza * coeficiente * (referencia->refleja_fuerza() ? 2.0f : 1.0f);
}

atributo::Velocidad::Velocidad(Vector2 magnitud = Vector2())
    : m_magnitud(magnitud)
{
}

void atributo::Velocidad::actualizar()
{
}

bool atributo::Velocidad::interactuar(ParticulaDinamica *referencia, atributo::Interaccion interaccion)
{
    if (referencia->en_historial(interaccion.m_particula))
        return false;

    Vector2 fuerza_choque = fuerza_de_choque(referencia, interaccion.m_particula, interaccion.m_direccion);

    if (!(fuerza_choque * interaccion.m_direccion) || !(referencia->m_velocidad.m_magnitud * interaccion.m_direccion))
        return false;

    referencia->m_fuerza += (fuerza_choque * -1.0f);
    interaccion.m_particula->m_fuerza += fuerza_choque;

    return true;
}

void atributo::Velocidad::operator+=(atributo::Velocidad otro)
{
    m_magnitud += otro.m_magnitud;
}

atributo::Torque::Torque(float magnitud = .0f)
    : m_magnitud(magnitud)
{
}

void atributo::Torque::actualizar()
{
}

void atributo::Torque::avanzar(ParticulaDinamica *referencia, float dt)
{
    referencia->m_velocidad_angular.m_magnitud += (m_magnitud * dt) / referencia->m_cuerpo->inercia;
}

void atributo::Torque::operator+=(atributo::Torque otro)
{
    m_magnitud += otro.m_magnitud;
}

atributo::VelocidadAngular::VelocidadAngular(float magnitud = .0f)
    : m_magnitud(magnitud)
{
}

void atributo::VelocidadAngular::actualizar()
{
}

bool atributo::VelocidadAngular::interactuar(ParticulaDinamica *referencia, Interaccion interaccion)
{
    return true;
}

void atributo::VelocidadAngular::operator+=(atributo::VelocidadAngular otro)
{
    m_magnitud += otro.m_magnitud;
}