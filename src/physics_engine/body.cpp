#include "body.h"

Body::Body()
    : Entidad(), c_vel(Vector2()), c_acc(Vector2()), c_masa(1.0f)
{
}

Body::Body(const Vector2 &pos)
    : Entidad(pos), c_vel(Vector2()), c_acc(Vector2()), c_masa(1.0f)
{
}

Body::Body(const Vector2 &pos, float masa)
    : Entidad(pos), c_vel(Vector2()), c_acc(Vector2()), c_masa(masa)
{
}

void Body::actualizar()
{
}
