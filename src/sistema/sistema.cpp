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
