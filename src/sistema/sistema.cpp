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

void Sistema::agregar_interaccion(Particula *particula, Particula *referencia)
{
    particula->agregar_interaccion(referencia);
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

Particula::Particula(cr::InfoCuerpo *info, Vector2 velocidad, float velocidad_angular, float coeficiente)
    : m_info(info), m_coeficiente(coeficiente), m_es_estatico(false)
{
}

Particula::Particula(cr::InfoCuerpo *info)
    : m_info(info), m_es_estatico(true)
{
}

void Particula::agregar_interaccion(Particula *referencia)
{
    for (Interaccion interaccion : m_interacciones)
        if (interaccion.particula == referencia)
            return;

    cr::PuntoDeColision pdc = m_info->cuerpo->punto_de_colision(referencia->m_info->cuerpo);
    Interaccion interaccion = {referencia, pdc.normal, pdc.caracteristica};

    m_interacciones.emplace_back(interaccion);
}

bool Particula::expandir()
{
    // if ((m_fuerza.nulo() && m_velocidad.nulo()) || m_es_estatico)
    // if (m_velocidad.nulo() || m_es_estatico)
    if (m_es_estatico)
        return true;

    bool hay_interaccion = false;
    for (Interaccion interaccion : m_interacciones)
    {
        // bool resultado = this->choque_de_fuerzas(interaccion.particula, interaccion.normal, interaccion.impacto);
        // bool resultado |= this->choque_de_velocidades(interaccion.particula, interaccion.normal, interaccion.impacto);
        // bool resultado = this->choque_de_velocidades(interaccion.particula, interaccion.normal, interaccion.impacto);
        bool resultado = false;
        if (resultado)
            agregar_elemento(interaccion.particula);
        hay_interaccion |= resultado;
    }

    return !hay_interaccion;
}

void Particula::actualizar()
{
    resetear();
    if (m_es_estatico)
        return;

    for (Intercambio *intercambio : m_fuerzas)
        intercambio->actualizar(); 
}

void Particula::aplicar_fuerza(Intercambio *intercambio)
{
    m_fuerzas.emplace_back(intercambio);
}

void Particula::afectar_velocidad(Vector2 magnitud)
{
    if (m_es_estatico)
        return;
    m_velocidad += magnitud / m_info->masa;
}

void Particula::afectar_rotacion(float magnitud)
{
    if (m_es_estatico)
        return;
    m_velocidad_angular += magnitud / m_info->inercia;
}

// void Particula::aplicar_torque(float torque)
// {
//     m_torque += torque;
// }

// void Particula::aplicar_fuerza(Vector2 fuerza)
// {
//     m_fuerza += fuerza;
//     m_fuerza_guardada = m_fuerza;
// }

// bool Particula::choque_de_fuerzas(Particula *particula, Vector2 &normal, Caracteristica impacto)
// {
//     if (m_es_estatico || particula->en_historial(this))
//         return false;

//     Vector2 fuerza_resultante = m_fuerza.proyeccion(normal);

//     if (fuerza_resultante * normal > 0)
//     {
//         // particula->m_fuerza_guardada += fuerza_resultante;
//         particula->rotacion_por_choque(fuerza_resultante, impacto);

//         // m_fuerza_guardada -= fuerza_resultante;
//         rotacion_por_choque(fuerza_resultante * -1.0f, impacto);
//         return true;
//     }

//     return false;
// }

// void Particula::rotacion_por_choque(Vector2 fuerza, Caracteristica impacto)
// {
//     for (int i = 0; i < impacto.cantidad(); i++)
//     {
//         // (impacto[i] - m_cuerpo->m_posicion).imprimir();
//         m_torque += (impacto[i] - m_cuerpo->m_posicion).vectorial(fuerza);
//     }
// }

// bool Particula::choque_de_velocidades(Particula *particula, Vector2 &normal, Caracteristica impacto)
// {
//     if (m_es_estatico || particula->en_historial(this))
//         return false;

//     Vector2 fuerza_choque = fuerza_de_choque(particula, normal);

//     if (fuerza_choque * normal > 0 && m_velocidad * normal > 0)
//     {
//         particula->m_velocidad_guardada += fuerza_choque / particula->m_info->masa;
//         // particula->rotacion_por_choque(fuerza_choque, impacto);

//         m_velocidad_guardada -= fuerza_choque / m_info->masa;
//         // rotacion_por_choque(fuerza_choque * -1.0f, impacto);
//         return true;
//     }

//     return false;
// }

// Vector2 Particula::fuerza_de_choque(Particula *particula, Vector2 &direccion)
// {
//     float masa = (particula->m_es_estatico) ? m_info->masa : particula->m_info->masa;
//     float coeficiente = (particula->m_es_estatico) ? m_coeficiente : particula->m_coeficiente;

//     float coeficiente_total = (m_coeficiente + coeficiente) / 4.0f + .5f;

//     Vector2 velocidad_relativa = velocidad_en_direccion(direccion) - particula->velocidad_en_direccion(direccion);
//     float promedio_de_masas = (m_info->masa + masa) / 2.0f;

//     Vector2 fuerza = (velocidad_relativa * m_info->masa * masa) / (promedio_de_masas);

//     return fuerza * coeficiente_total * (particula->m_es_estatico ? 2.0f : 1.0f);
// }

// Vector2 Particula::velocidad_en_direccion(Vector2 &direccion)
// {
//     return m_velocidad.proyeccion(direccion);
// }

Intercambio::Intercambio(Vector2 magnitud)
    : m_magnitud(magnitud), m_magnitud_reservada(magnitud)
{
}

void Intercambio::actualizar()
{
    m_magnitud = m_magnitud_reservada;
}

Velocidad::Velocidad(Vector2 magnitud)
    : Intercambio(magnitud)
{
}

void Velocidad::aplicar(Vector2 direccion, Particula *particula)
{
}

Fuerza::Fuerza(Vector2 magnitud)
    : Intercambio(magnitud)
{
}

void Fuerza::aplicar(Vector2 direccion, Particula *particula)
{
    if (m_magnitud * direccion <= 0)
        return;

    Vector2 fuerza_direccionada = m_magnitud.proyeccion(direccion);
    particula->afectar_velocidad(fuerza_direccionada);
    m_magnitud_reservada -= fuerza_direccionada;
}

Intercambio *Fuerza::en_dir(Vector2 direccion)
{
    m_magnitud = m_magnitud.proyeccion(direccion);
    return this;
}

VelocidadAngular::VelocidadAngular(Vector2 magnitud)
    : Intercambio(magnitud)
{
}

void VelocidadAngular::aplicar(Vector2 direccion, Particula *particula)
{
}

Torque::Torque(Vector2 magnitud)
    : Intercambio(magnitud)
{
}

void Torque::aplicar(Vector2 direccion, Particula *particula)
{
}