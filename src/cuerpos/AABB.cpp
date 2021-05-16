#include "AABB.h"

#include "colisiones.cpp"

AABB::AABB(Vector2 posicion, float ancho, float alto)
    : CuerpoRigido(posicion), m_ancho(ancho), m_alto(alto)
{
}

PuntoDeColision AABB::colisiona(CuerpoRigido *cuerpo_rigido)
{
    return cuerpo_rigido->colisiona(this);
}

PuntoDeColision AABB::colisiona(Circulo *circulo)
{
    return colision::colision_circulo_aabb(circulo, this).invertir();
}

PuntoDeColision AABB::colisiona(Linea *linea)
{
    return colision::colision_aabb_linea(this, linea);
}

PuntoDeColision AABB::colisiona(AABB *aabb)
{
    return colision::colision_aabb_aabb(this, aabb);
}

Vector2 AABB::punto_borde(const Vector2 &direccion) const
{
    float relacion = (direccion.y == 0) ? 0 : direccion.x / direccion.y;
    float valor = (relacion > 1 || relacion < -1) ? m_ancho / direccion.x : m_alto / direccion.y;
    return (direccion * valor);
}