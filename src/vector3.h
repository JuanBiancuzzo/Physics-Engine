#pragma once
#include "vector2.h"

struct Vector2;

struct Vector3
{
    float x, y, z;

    Vector3();
    Vector3(float x, float y, float z);

    Vector3 operator+(const Vector3 &otro) const;
    Vector3 operator-(const Vector3 &otro) const;
    float operator*(const Vector3 &otro) const; // producto escalar
    Vector3 operator*(float alpha) const;
    Vector3 operator/(float alpha) const;

    void operator+=(const Vector3 &otro);
    void operator-=(const Vector3 &otro);
    void operator*=(float alpha);
    void operator/=(float alpha);

    bool operator==(const Vector3 &otro) const;
    Vector3 operator=(const Vector2 &otro);

    float modulo() const;
    float modulo_cuadrado() const;

    float distancia(const Vector3 &otro) const;
    float distancia_cuadrada(const Vector3 &otro) const;

    Vector3 vectorial(const Vector3 &otro) const;
    Vector2 dos_dimensiones() const;

    Vector3 proyeccion(const Vector3 &otro) const;
    Vector3 normal() const;

    bool nulo() const;
};
