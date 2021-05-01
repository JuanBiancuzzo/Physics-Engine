#include "body.h"

Body::Body()
    : Entidad(), c_vel(Vector2()), c_acc(Vector2()), c_masa(1.0f), c_estructura(nullptr)
{
}

Body::Body(const Vector2 &pos)
    : Entidad(pos), c_vel(Vector2()), c_acc(Vector2()), c_masa(1.0f), c_estructura(nullptr)
{
}

Body::Body(const Vector2 &pos, Area *estructura)
    : Entidad(pos), c_vel(Vector2()), c_acc(Vector2()), c_masa(1.0f), c_estructura(estructura)
{
}

Body::Body(const Vector2 &pos, float masa)
    : Entidad(pos), c_vel(Vector2()), c_acc(Vector2()), c_masa(masa), c_estructura(nullptr)
{
}

Body::Body(const Vector2 &pos, float masa, Area *estructura)
    : Entidad(pos), c_vel(Vector2()), c_acc(Vector2()), c_masa(masa), c_estructura(estructura)
{
}

void Body::actualizar(const float dt)
{
    c_vel += c_acc * dt;
    c_estructura->c_pos += c_vel * dt;
}
