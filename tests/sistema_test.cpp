#include "gtest/gtest.h"
#include "../src/sistema.h"

using namespace sistema;

// test donde hay un piso, y dos particulas una encima de la otra
TEST(SistemaTest, Dos_particulas_y_el_piso_sin_velocidad_ninguna_sus_fuerzas_finales_son_cero)
{
    std::vector<Particula *> particulas;
    Vector2 fuerza_particula_1(.0f, -10.0f), fuerza_particula_2(.0f, -20.0f), nulo;
    particulas.emplace_back(new Particula(fuerza_particula_1, nulo));
    particulas.emplace_back(new Particula(fuerza_particula_2, nulo));
    particulas.emplace_back(new Particula(true));
    Vector2 dir_abajo(.0f, -1.0f);
    Vector2 dir_arriba(.0f, 1.0f);
    Interaccion hacia_abajo(dir_abajo);
    Interaccion hacia_arriba(dir_arriba);

    Sistema sistema(particulas);
    sistema.agreagar_interaccion(particulas[0], particulas[1], &hacia_abajo);
    sistema.agreagar_interaccion(particulas[1], particulas[2], &hacia_abajo);
    sistema.agreagar_interaccion(particulas[2], particulas[1], &hacia_arriba);
    sistema.agreagar_interaccion(particulas[1], particulas[0], &hacia_arriba);

    sistema.expandir_fuerzas();

    ASSERT_EQ(particulas[0]->m_fuerza, Vector2());
    ASSERT_EQ(particulas[1]->m_fuerza, Vector2());

    for (Particula *particula : particulas)
        delete particula;
}

// test donde hay dos particulas cayendose, a la misma velocidad por lo que no deberia haber un choque -> a determinar

// test donde hay dos particulas cayendose, la de abajo con una mayor velocidad por lo que no deberia haber un choque -> a determinar

// test donde hay dos particulas cayendose, la de arriba con mayor velocidad produciendose un choque

// test donde hay una bala y un cuerpo sin fuerza inicial volando, y terminan intercambiando velocidades