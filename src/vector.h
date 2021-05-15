#pragma once

#include <iostream>

struct Vector2
{
    float x, y;

    Vector2();

    Vector2(float x, float y);

    Vector2 operator+(const Vector2 &otro) const;
    Vector2 operator-(const Vector2 &otro) const;
    float operator*(const Vector2 &otro) const; // producto interno
    Vector2 operator*(float alpha) const;
    Vector2 operator/(float alpha) const;

    void operator+=(const Vector2 &otro);
    void operator-=(const Vector2 &otro);
    void operator*=(float alpha);
    void operator/=(float alpha);

    bool operator==(const Vector2 &otro) const;

    float modulo() const;
    float modulo_cuadrado() const;

    float distancia(const Vector2 &otro) const;
    float distancia_cuadrada(const Vector2 &otro) const;

    Vector2 proyeccion(const Vector2 &otro) const;
    Vector2 normal() const;

    void imprimir() const;
};