#include "headers/vector.h"

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

float Vector2::modulo() const
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

float Vector2::distancia(const Vector2 &otro) const 
{
    return (*this - otro).modulo();
}

void Vector2::imprimir() const 
{
    std::cout << x << ", " << y << std::endl;
}
