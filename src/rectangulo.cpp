
#include "headers/rectangulo.h"

Rectangulo::Rectangulo(const Vector2 pos)
    : c_pos(pos), c_w(1.0f), c_h(1.0f)
{
}

Rectangulo::Rectangulo(const Vector2 pos, float w, float h)
    : c_pos(pos), c_w(w), c_h(h)
{
}

bool Rectangulo::contiene(const Particula &particula) const
{
    return !(
        c_pos.x + c_w <= particula.c_pos.x - particula.c_radio ||
        c_pos.x - c_w >= particula.c_pos.x + particula.c_radio ||
        c_pos.y + c_h <= particula.c_pos.y - particula.c_radio ||
        c_pos.y - c_h >= particula.c_pos.y + particula.c_radio);
}

bool Rectangulo::intersecta(const Rectangulo &frontera) const
{
    return !(
        c_pos.x + c_w <= frontera.c_pos.x - frontera.c_w ||
        c_pos.x - c_w >= frontera.c_pos.x + frontera.c_w ||
        c_pos.y + c_h <= frontera.c_pos.y - frontera.c_h ||
        c_pos.y - c_h >= frontera.c_pos.y + frontera.c_h);
}