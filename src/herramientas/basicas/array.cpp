#include "headers/array.h"
#include <stdlib.h>

template <typename T>
Array<T>::Array()
    : c_cantidad(1), c_capacidad(3), c_factor_completitud(0.8f)
{
    c_array = calloc(c_cantidad, sizeof(T));
}

template <typename T>
Array<T>::Array(int cantidad_inicial)
    : c_cantidad(1), c_capacidad(3), c_factor_completitud(0.8f)
{
    if (cantidad_inicial > c_cantidad)
        c_cantidad = cantidad_inicial;
    c_array = calloc(c_cantidad, sizeof(T));
}

template <typename T>
Array<T>::~Array()
{
    free(c_array);
}

template <typename T>
T Array<T>::operator[](int index)
{
    return *(c_array + sizeof(T) * index);
}

template <typename T>
void Array<T>::insertar(T valor)
{
    if (!tiene_capacidad())
        expandir();
    c_array[c_cantidad] = valor;
    c_cantidad++;
}

template <typename T>
int Array<T>::cantidad()
{
    return c_cantidad;
}

template <typename T>
bool Array<T>::tiene_capacidad()
{
    return (c_capacidad * c_factor_completitud > c_cantidad);
}

template <typename T>
void Array<T>::expandir()
{
    c_capacidad *= 1.3f;
    do
    {
        T *aux = realloc(c_array, (size_t)c_capacidad);
    } while (!aux);
    c_array = aux;
}