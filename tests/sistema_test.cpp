#include "gtest/gtest.h"
#include "../src/sistema.h"

using namespace sistema;

// test donde hay un piso, y dos particulas una encima de la otra
TEST(SistemaTest, Dos_particulas_y_el_piso_sin_velocidad_ninguna_sus_fuerzas_finales_son_cero)
{
    std::vector<Particula *> particulas;
    Particula *particula1 = new Particula(Vector2(.0f, -10.0f));
    Particula *particula2 = new Particula(Vector2(.0f, -20.0f));
    Particula_estatica *piso = new Particula_estatica();

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);
    particulas.emplace_back(piso);

    Sistema sistema(particulas);

    Vector2 dir_abajo(.0f, -1.0f), dir_arriba(.0f, 1.0f);
    sistema.agregar_interaccion(particula1, particula2, dir_abajo);
    sistema.agregar_interaccion(particula2, piso, dir_abajo);
    sistema.agregar_interaccion(piso, particula2, dir_arriba);
    sistema.agregar_interaccion(particula2, particula1, dir_arriba);

    sistema.expandir_fuerzas();

    ASSERT_EQ(particula1->m_fuerza, Vector2());
    ASSERT_EQ(particula2->m_fuerza, Vector2());
}

TEST(SistemaTest, Dos_particulas_y_el_piso_el_primero_con_velocidad_sus_fuerzas_finales_son_cero)
{
}

// test donde hay dos particulas cayendose, a la misma velocidad por lo que no deberia haber un choque -> a determinar

// test donde hay dos particulas cayendose, la de abajo con una mayor velocidad por lo que no deberia haber un choque -> a determinar

// test donde hay dos particulas cayendose, la de arriba con mayor velocidad produciendose un choque

// test donde hay una bala y un cuerpo sin fuerza inicial volando, y terminan intercambiando velocidades
TEST(SistemaTest, Una_bala_con_velocidad_y_un_bloque_sin_velcodad_chocan_e_intercambian_velocidades)
{
}