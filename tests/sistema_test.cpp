#include "gtest/gtest.h"
#include "../src/sistema.h"

using namespace sistema;

// test donde hay un piso, y dos particulas una encima de la otra
TEST(SistemaTest, Dos_particulas_y_el_piso_sin_velocidad_ninguna_sus_fuerzas_finales_son_cero)
{
    std::vector<Particula *> particulas;
    Particula *particula1 = new Particula(1.0f, Vector2(), Vector2(.0f, -10.0f));
    Particula *particula2 = new Particula(2.0f, Vector2(), Vector2(.0f, -20.0f));
    Particula *piso = new Particula();

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);
    particulas.emplace_back(piso);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_abajo(.0f, -1.0f), dir_arriba(.0f, 1.0f);
    sistema.agregar_interaccion(particula1, particula2, dir_abajo);
    sistema.agregar_interaccion(particula2, piso, dir_abajo);
    sistema.agregar_interaccion(piso, particula2, dir_arriba);
    sistema.agregar_interaccion(particula2, particula1, dir_arriba);

    sistema.expandir_fuerzas();

    ASSERT_EQ(particula1->m_fuerza, Vector2());
    ASSERT_EQ(particula2->m_fuerza, Vector2());
}

TEST(SistemaTest, Dos_particulas_y_el_piso_el_primero_con_velocidad_y_rebota_con_su_velocidad_invertida)
{
    std::vector<Particula *> particulas;
    Particula *particula1 = new Particula(1.0f, Vector2(.0f, -10.0f), Vector2(.0f, -10.0f));
    Particula *particula2 = new Particula(2.0f, Vector2(), Vector2(.0f, -20.0f));
    Particula *piso = new Particula();

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);
    particulas.emplace_back(piso);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_abajo(.0f, -1.0f), dir_arriba(.0f, 1.0f);
    sistema.agregar_interaccion(particula1, particula2, dir_abajo);
    sistema.agregar_interaccion(particula2, piso, dir_abajo);
    sistema.agregar_interaccion(piso, particula2, dir_arriba);
    sistema.agregar_interaccion(particula2, particula1, dir_arriba);

    std::cout << "Antes" << std::endl;
    for (Particula *particula : particulas)
        std::cout << particula->m_velocidad.x << ", " << particula->m_velocidad.y << std::endl;

    sistema.expandir_fuerzas();

    std::cout << "Despues" << std::endl;
    for (Particula *particula : particulas)
        std::cout << particula->m_velocidad.x << ", " << particula->m_velocidad.y << std::endl;

    ASSERT_EQ(particula1->m_velocidad, Vector2(.0f, 10.0f));
    ASSERT_EQ(particula2->m_velocidad, Vector2());
}

TEST(SistemaTest, Dos_particulas_sobre_el_piso_una_tiene_velocidad_y_terminan_intercambiando_velocidades)
{
    std::vector<Particula *> particulas;
    Particula *particula1 = new Particula(1.0f, Vector2(10.0f, .0f), Vector2(.0f, -10.0f));
    Particula *particula2 = new Particula(1.0f, Vector2(), Vector2(.0f, -10.0f));
    Particula *piso = new Particula();

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);
    particulas.emplace_back(piso);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_abajo(.0f, -1.0f), dir_arriba(.0f, 1.0f), dir_derecha(1.0f, .0f), dir_izquierda(-1.0f, .0f);
    sistema.agregar_interaccion(particula1, piso, dir_abajo);
    sistema.agregar_interaccion(particula2, piso, dir_abajo);
    sistema.agregar_interaccion(piso, particula2, dir_arriba);
    sistema.agregar_interaccion(piso, particula1, dir_arriba);
    sistema.agregar_interaccion(particula1, particula2, dir_derecha);
    sistema.agregar_interaccion(particula2, particula1, dir_izquierda);

    sistema.expandir_fuerzas();

    ASSERT_EQ(particula1->m_velocidad, Vector2());
    ASSERT_EQ(particula1->m_fuerza, Vector2());

    ASSERT_EQ(particula2->m_velocidad, Vector2(10.0f, .0f));
    ASSERT_EQ(particula2->m_fuerza, Vector2());
}

TEST(SistemaTest, Dos_particulas_sobre_el_piso_una_tienen_velocidades_y_hay_un_choque_elastico)
{
    std::vector<Particula *> particulas;
    Particula *particula1 = new Particula(1.0f, Vector2(30.0f, .0f), Vector2(.0f, -10.0f));
    Particula *particula2 = new Particula(2.0f, Vector2(-30.0f, .0f), Vector2(.0f, -20.0f));
    Particula *piso = new Particula();

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);
    particulas.emplace_back(piso);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_abajo(.0f, -1.0f), dir_arriba(.0f, 1.0f), dir_derecha(1.0f, .0f), dir_izquierda(-1.0f, .0f);
    sistema.agregar_interaccion(particula1, piso, dir_abajo);
    sistema.agregar_interaccion(particula2, piso, dir_abajo);
    sistema.agregar_interaccion(piso, particula2, dir_arriba);
    sistema.agregar_interaccion(piso, particula1, dir_arriba);
    sistema.agregar_interaccion(particula1, particula2, dir_derecha);
    sistema.agregar_interaccion(particula2, particula1, dir_izquierda);

    sistema.expandir_fuerzas();

    ASSERT_EQ(particula1->m_velocidad, Vector2(-50.0f, .0f));
    ASSERT_EQ(particula1->m_fuerza, Vector2());
    ASSERT_EQ(particula2->m_velocidad, Vector2(10.0f, .0f));
    ASSERT_EQ(particula2->m_fuerza, Vector2());
}

// test donde hay dos particulas cayendose, a la misma velocidad por lo que no deberia haber un choque -> a determinar

// test donde hay dos particulas cayendose, la de abajo con una mayor velocidad por lo que no deberia haber un choque -> a determinar

// test donde hay dos particulas cayendose, la de arriba con mayor velocidad produciendose un choque