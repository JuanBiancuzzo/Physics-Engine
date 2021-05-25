#include "colisiones.h"

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
        Vector2 dir(linea->m_final - linea->m_pos);
        Vector2 t_cerca(((aabb->m_pos.x - aabb->m_ancho) - linea->m_pos.x) / dir.x,
                        ((aabb->m_pos.y - aabb->m_ancho) - linea->m_pos.y) / dir.y);
        Vector2 t_lejos(((aabb->m_pos.x + aabb->m_ancho) - linea->m_pos.x) / dir.x,
                        ((aabb->m_pos.y - aabb->m_ancho) - linea->m_pos.y) / dir.y);

        if (t_cerca.x > t_lejos.x)
            std::swap(t_cerca.x, t_lejos.x);
        if (t_cerca.y > t_lejos.y)
            std::swap(t_cerca.y, t_lejos.y);

        bool colisionan = !(t_cerca.x > t_lejos.y || t_cerca.y > t_lejos.x);

        float t_cerca_colision = std::max<float>(t_cerca.x, t_cerca.y);
        float t_lejos_colision = std::min<float>(t_lejos.x, t_lejos.y);

        Vector2 A = linea->m_pos + dir * t_cerca_colision;
        Vector2 B = linea->m_pos + dir * t_lejos_colision;

        colisionan = (colisionan) ? !(t_lejos_colision < 0) : colisionan;

        return {A, B, (B - A).normal(), (B - A).modulo(), colisionan};
    }
}