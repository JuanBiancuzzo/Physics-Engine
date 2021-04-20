#pragma once

#include <iostream>

struct Vector2
{
    float x, y;

    Vector2();

    Vector2(float x, float y);

    Vector2 operator+(const Vector2 &otro) const;

    Vector2 operator-(const Vector2 &otro) const;

    Vector2 operator*(float alpha) const;

    Vector2 operator/(float alpha) const;

    float operator*(const Vector2 &otro) const; // producto interno

    void operator+=(const Vector2 &otro);

    void operator-=(const Vector2 &otro);

    void operator*=(float alpha);

    float modulo() const;

    float distancia(const Vector2 &otro) const;

    void imprimir() const;
};
