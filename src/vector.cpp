#include "vector.h"

#include <math.h>

Vector2::Vector2() : x(.0f), y(.0f) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2 &otro) const
{
    return Vector2(x + otro.x, y + otro.y);
}

Vector2 Vector2::operator-(const Vector2 &otro) const
{
    return Vector2(x - otro.x, y - otro.y);
}

Vector2 Vector2::operator*(float alpha) const
{
    return Vector2(x * alpha, y * alpha);
}

float Vector2::operator*(const Vector2 &otro) const
{
    return (x * otro.x + y * otro.y);
}

Vector2 Vector2::operator/(float alpha) const
{
    return Vector2(x / alpha, y / alpha);
}

void Vector2::operator+=(const Vector2 &otro)
{
    x += otro.x;
    y += otro.y;
}

void Vector2::operator-=(const Vector2 &otro)
{
    x -= otro.x;
    y -= otro.y;
}

void Vector2::operator*=(float alpha)
{
    *this = *this * alpha;
}

void Vector2::operator/=(float alpha)
{
    *this = *this / alpha;
}

bool Vector2::operator==(const Vector2 &otro) const
{
    bool en_x = (this->x - delta < otro.x and otro.x < this->x + delta);
    bool en_y = (this->y - delta < otro.y and otro.y < this->y + delta);

    return en_x && en_y;
}

float Vector2::modulo() const
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

float Vector2::modulo_cuadrado() const
{
    return pow(x, 2) + pow(y, 2);
}

float Vector2::distancia(const Vector2 &otro) const
{
    return (*this - otro).modulo();
}

float Vector2::distancia_cuadrada(const Vector2 &otro) const
{
    return pow(x - otro.x, 2) + pow(y - otro.y, 2);
}

Vector2 Vector2::proyeccion(const Vector2 &otro) const
{
    return otro * (((*this) * otro) / otro.modulo_cuadrado());
}

Vector2 Vector2::normal() const
{
    if (this->modulo() == 0.0f)
        return *this;
    return (*this / this->modulo());
}

Vector2 Vector2::perp_en_dir(const Vector2 &otro, const Vector2 &dir) const
{
    Vector2 AB = otro - *this, AD = dir - *this;

    float producto_vectorial = AB.x * AD.y - AB.y * AD.x;
    return Vector2(-1.0f * AB.y * producto_vectorial, AB.x * producto_vectorial).normal();
}

bool Vector2::nulo() const
{
    return (*this == *this * .0f);
}