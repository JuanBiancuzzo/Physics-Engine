#pragma once

template <typename T>
class Array
{
private:
    T *c_array;
    int c_cantidad;
    int c_capacidad;
    float c_factor_completitud;

public:
    Array();
    Array(int cantidad_inicial);
    ~Array();

    T operator[](int index);
    void operator=(T valor) = delete;
    void insertar(T valor);
    int cantidad();

private:
    bool tiene_capacidad();
    void expandir();
};
