#include "cuerpoRigido.h"

#include "cuerpos.h"

namespace colision
{
    PuntoDeColision colision_circulo_circulo(Circulo *prin, Circulo *secun)
    {
        Vector2 A = (secun->m_pos - prin->m_pos).normal() * prin->m_radio;
        Vector2 B = (prin->m_pos - secun->m_pos).normal() * secun->m_radio;
        bool colisionan = prin->m_radio + secun->m_radio >= (prin->m_pos - secun->m_pos).modulo();

        return {A, B, (B - A).normal(), (B - A).modulo(), colisionan};
    }

    PuntoDeColision colision_circulo_linea(Circulo *circulo, Linea *linea)
    {
        float proyeccion = (linea->m_final - linea->m_pos) * (circulo->m_pos - linea->m_pos);
        float largo = (linea->m_final - linea->m_pos).modulo_cuadrado();

        float t = std::max<float>(.0f, std::min<float>(largo, proyeccion)) / largo;

        Vector2 B = linea->m_pos + (linea->m_final - linea->m_pos) * t;
        Vector2 A = (B - circulo->m_pos).normal() * circulo->m_radio;
        bool colisionan = circulo->m_radio >= (B - circulo->m_pos).modulo();

        return {A, B, (B - A).normal(), (B - A).modulo(), colisionan};
    }

    PuntoDeColision colision_linea_linea(Linea *prin, Linea *secun)
    {
        return {}; // no quiero colisiones entre linea y circulo
    }

    PuntoDeColision colision_aabb_aabb(AABB *prin, AABB *secun)
    {
        Vector2 diferencia = secun->m_pos - prin->m_pos;
        Vector2 A = prin->punto_borde(diferencia);
        Vector2 B = secun->punto_borde(diferencia * -1.0f);
        bool colisionan = prin->m_pos.distancia_cuadrada(A) + secun->m_pos.distancia_cuadrada(B) >= diferencia.modulo_cuadrado();

        return {A, B, (B - A).normal(), (B - A).modulo(), colisionan};
    }

    PuntoDeColision colision_circulo_aabb(Circulo *circulo, AABB *aabb)
    {
        Vector2 diferencia = aabb->m_pos - circulo->m_pos;
        Vector2 A = diferencia.normal() * circulo->m_radio;
        Vector2 B = aabb->punto_borde(diferencia * -1.0f);
        bool colisionan = circulo->m_pos.distancia_cuadrada(A) + aabb->m_pos.distancia_cuadrada(B) >= diferencia.modulo_cuadrado();

        return {A, B, (B - A).normal(), (B - A).modulo(), colisionan};
    }

    PuntoDeColision colision_aabb_linea(AABB *aabb, Linea *linea)
    {
        // implementar

        return {};
    }
}