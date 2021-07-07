#include "colisiones.h"

namespace colision
{
    PuntoDeColision colision_circulo_circulo(Circulo *prin, Circulo *secun)
    {
        Vector2 A = (secun->m_posicion - prin->m_posicion).normal() * prin->m_radio;
        Vector2 B = (prin->m_posicion - secun->m_posicion).normal() * secun->m_radio;
        bool colisionan = prin->m_radio + secun->m_radio >= (prin->m_posicion - secun->m_posicion).modulo();

        return {A, B, (B - A).normal(), (B - A).modulo(), colisionan};
    }

    PuntoDeColision colision_circulo_linea(Circulo *circulo, Linea *linea)
    {
        float proyeccion = (linea->m_final - linea->m_posicion) * (circulo->m_posicion - linea->m_posicion);
        float largo = (linea->m_final - linea->m_posicion).modulo_cuadrado();

        float t = std::max<float>(.0f, std::min<float>(largo, proyeccion)) / largo;

        Vector2 B = linea->m_posicion + (linea->m_final - linea->m_posicion) * t;
        Vector2 A = B.normal() * circulo->m_radio;
        bool colisionan = circulo->m_radio >= B.modulo();

        return {A, B, (B - A).normal(), (B - A).modulo(), colisionan};
    }

    PuntoDeColision colision_linea_linea(Linea *prin, Linea *secun)
    {
        return {}; // no quiero colisiones entre linea y circulo
    }

    PuntoDeColision colision_aabb_aabb(AABB *prin, AABB *secun)
    {
        Vector2 diferencia = secun->m_posicion - prin->m_posicion;
        Vector2 A = prin->punto_borde(diferencia);
        diferencia *= -1.0f;
        Vector2 B = secun->punto_borde(diferencia);
        bool colisionan = A.modulo() + B.modulo() >= diferencia.modulo();

        return {A, B, (B - A).normal(), (B - A).modulo(), colisionan};
    }

    PuntoDeColision colision_circulo_aabb(Circulo *circulo, AABB *aabb)
    {
        Vector2 diferencia = aabb->m_posicion - circulo->m_posicion;
        Vector2 A = diferencia.normal() * circulo->m_radio;
        diferencia *= -1.0f;
        Vector2 B = aabb->punto_borde(diferencia);
        bool colisionan = A.modulo() + B.modulo() >= diferencia.modulo();

        return {A, B, (B - A).normal(), (B - A).modulo(), colisionan};
    }

    PuntoDeColision colision_aabb_linea(AABB *aabb, Linea *linea)
    {
        Vector2 dir(linea->m_final - linea->m_posicion);
        Vector2 t_cerca(((aabb->m_posicion.x - aabb->m_ancho) - linea->m_posicion.x) / dir.x,
                        ((aabb->m_posicion.y - aabb->m_ancho) - linea->m_posicion.y) / dir.y);
        Vector2 t_lejos(((aabb->m_posicion.x + aabb->m_ancho) - linea->m_posicion.x) / dir.x,
                        ((aabb->m_posicion.y - aabb->m_ancho) - linea->m_posicion.y) / dir.y);

        if (t_cerca.x > t_lejos.x)
            std::swap(t_cerca.x, t_lejos.x);
        if (t_cerca.y > t_lejos.y)
            std::swap(t_cerca.y, t_lejos.y);

        bool colisionan = !(t_cerca.x > t_lejos.y || t_cerca.y > t_lejos.x);

        float t_cerca_colision = std::max<float>(t_cerca.x, t_cerca.y);
        float t_lejos_colision = std::min<float>(t_lejos.x, t_lejos.y);

        Vector2 A = linea->m_posicion + dir * t_cerca_colision;
        Vector2 B = linea->m_posicion + dir * t_lejos_colision;

        colisionan = (colisionan) ? !(t_lejos_colision < 0) : colisionan;

        return {A, B, (B - A).normal(), (B - A).modulo(), colisionan};
    }
}