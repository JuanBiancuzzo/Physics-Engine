#include "vector.h"

#include <math.h>

Vector2::Vector2()
    : x(.0f), y(.0f)
{
}

Vector2::Vector2(float x, float y)
    : x(x), y(y)
{
}

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
    return (*this - otro).modulo_cuadrado();
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

Vector2 Vector2::perpendicular() const
{
    return Vector2(-1.0f * y, x);
}

Vector2 Vector2::rotar(float radianes) const
{
    float x_prima = x * cos(radianes) - y * sin(radianes);
    float y_prima = x * sin(radianes) + y * cos(radianes);
    return Vector2(x_prima, y_prima);
}

bool Vector2::nulo() const
{
    return (*this == *this * .0f);
}

Vector3::Vector3()
    : x(.0f), y(.0f), z(.0f)
{
}

Vector3::Vector3(float x, float y, float z)
    : x(x), y(y), z(z)
{
}

Vector3 Vector3::operator+(const Vector3 &otro) const
{
    return Vector3(x + otro.x, y + otro.y, z + otro.z);
}

Vector3 Vector3::operator-(const Vector3 &otro) const
{
    return Vector3(x - otro.x, y - otro.y, z - otro.z);
}

Vector3 Vector3::operator*(float alpha) const
{
    return Vector3(x * alpha, y * alpha, z * alpha);
}

float Vector3::operator*(const Vector3 &otro) const
{
    return (x * otro.x + y * otro.y + z * otro.z);
}

Vector3 Vector3::operator/(float alpha) const
{
    return Vector3(x / alpha, y / alpha, z / alpha);
}

void Vector3::operator+=(const Vector3 &otro)
{
    x += otro.x;
    y += otro.y;
    z += otro.z;
}

void Vector3::operator-=(const Vector3 &otro)
{
    x -= otro.x;
    y -= otro.y;
    z -= otro.z;
}

void Vector3::operator*=(float alpha)
{
    *this = *this * alpha;
}

void Vector3::operator/=(float alpha)
{
    *this = *this / alpha;
}

bool Vector3::operator==(const Vector3 &otro) const
{
    bool en_x = (this->x - delta < otro.x and otro.x < this->x + delta);
    bool en_y = (this->y - delta < otro.y and otro.y < this->y + delta);
    bool en_z = (this->z - delta < otro.z and otro.z < this->z + delta);

    return en_x && en_y && en_z;
}

Vector3 Vector3::operator=(const Vector2 &otro)
{
    x = otro.x;
    y = otro.y;
    z = .0f;
    return *this;
}

float Vector3::modulo() const
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

float Vector3::modulo_cuadrado() const
{
    return pow(x, 2) + pow(y, 2) + pow(z, 2);
}

float Vector3::distancia(const Vector3 &otro) const
{
    return (*this - otro).modulo();
}

float Vector3::distancia_cuadrada(const Vector3 &otro) const
{
    return (*this - otro).modulo_cuadrado();
}

Vector3 Vector3::vectorial(const Vector3 &otro) const
{
    float comp_x = y * otro.z - z * otro.y;
    float comp_y = z * otro.x - x * otro.z;
    float comp_z = x * otro.y - y * otro.x;

    return Vector3(comp_x, comp_y, comp_z);
}

Vector2 Vector3::dos_dimensiones() const
{
    return Vector2(x, y);
}

Vector3 Vector3::proyeccion(const Vector3 &otro) const
{
    return otro * (((*this) * otro) / otro.modulo_cuadrado());
}

Vector3 Vector3::normal() const
{
    if (this->modulo() == 0.0f)
        return *this;
    return (*this / this->modulo());
}

bool Vector3::nulo() const
{
    return (*this == *this * .0f);
}