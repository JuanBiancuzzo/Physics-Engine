
#include "area.h"

Area::Area(const Vector2 &pos)
    : c_pos(pos)
{
}

void Area::actualizar(Vector2 &pos)
{
    c_pos = pos;
}

Rectangulo::Rectangulo()
    : Area(Vector2()), c_w(1.0f), c_h(1.0f)
{
}

Rectangulo::Rectangulo(const Vector2 pos)
    : Area(pos), c_w(1.0f), c_h(1.0f)
{
}

Rectangulo::Rectangulo(const Vector2 pos, float w, float h)
    : Area(pos), c_w(w), c_h(h)
{
}

bool Rectangulo::contiene(const Vector2 &pos) const
{
    return !(c_pos.x + c_w < pos.x || c_pos.x - c_w > pos.x ||
             c_pos.y + c_h < pos.y || c_pos.y - c_h > pos.y);
}

float Rectangulo::distancia_borde_cuadrado(const Vector2 &dir) const
{
    float relacion = dir.x / dir.y;
    float valor = (relacion > 1 || relacion < -1) ? c_w / dir.x : c_h / dir.y;
    return (dir * valor).modulo_cuadrado();
}

bool Rectangulo::intersecta(const Area &frontera) const
{
    Vector2 delta = frontera.c_pos - c_pos;
    return (this->distancia_borde_cuadrado(delta) + frontera.distancia_borde_cuadrado(delta * -1) > delta.modulo_cuadrado());
}

Circulo::Circulo()
    : Area(Vector2()), c_r(1.0f)
{
}

Circulo::Circulo(const Vector2 pos)
    : Area(pos), c_r(1.0f)
{
}

Circulo::Circulo(const Vector2 pos, float r)
    : Area(pos), c_r(r)
{
}

bool Circulo::contiene(const Vector2 &pos) const
{
    return (c_pos.distancia_cuadrada(pos) < c_r * c_r);
}

float Circulo::distancia_borde_cuadrado(const Vector2 &dir) const
{
    return c_r * c_r;
}

bool Circulo::intersecta(const Area &frontera) const
{
    Vector2 delta = frontera.c_pos - c_pos;
    return (this->distancia_borde_cuadrado(delta) + frontera.distancia_borde_cuadrado(delta * -1) > delta.modulo_cuadrado());
}
