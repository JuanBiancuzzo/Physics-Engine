#include "gtest/gtest.h"
#include "../../../src/physics_engine/particula.h"

TEST(ParticulaTest, Inicializar_particula_sin_parametros)
{
    Particula particula;

    ASSERT_EQ(particula.c_pos, Vector2());
    ASSERT_EQ(particula.c_vel, Vector2());
    ASSERT_EQ(particula.c_acc, Vector2());
    ASSERT_EQ(particula.c_masa, 1.0f);
    ASSERT_EQ(particula.c_radio, 1.0f);
}

TEST(ParticulaTest, Inicializar_particula_con_posicion)
{
    Vector2 pos(45.67f, 545.32f);
    Particula particula(pos);

    ASSERT_EQ(particula.c_pos, pos);
    ASSERT_EQ(particula.c_vel, Vector2());
    ASSERT_EQ(particula.c_acc, Vector2());
    ASSERT_EQ(particula.c_masa, 1.0f);
    ASSERT_EQ(particula.c_radio, 1.0f);
}

TEST(ParticulaTest, Inicializar_particula_con_posicion_y_masa)
{
    Vector2 pos(45.67f, 545.32f);
    float masa = 54.4f;
    Particula particula(pos, masa);

    ASSERT_EQ(particula.c_pos, pos);
    ASSERT_EQ(particula.c_vel, Vector2());
    ASSERT_EQ(particula.c_acc, Vector2());
    ASSERT_EQ(particula.c_masa, masa);
    ASSERT_EQ(particula.c_radio, 1.0f);
}

TEST(ParticulaTest, Inicializar_particula_con_posicion_masa_y_radio)
{
    Vector2 pos(45.67f, 545.32f);
    float masa = 54.4f, radio = 32.0f;
    Particula particula(pos, masa, radio);

    ASSERT_EQ(particula.c_pos, pos);
    ASSERT_EQ(particula.c_vel, Vector2());
    ASSERT_EQ(particula.c_acc, Vector2());
    ASSERT_EQ(particula.c_masa, masa);
    ASSERT_EQ(particula.c_radio, radio);
}

TEST(ParticulaTest, aplicar_fuerza_con_masa_default)
{
    Particula particula;
    Vector2 fuerza(-1.0f, 1.0f);

    particula.aplicar_fuerza(fuerza);

    ASSERT_EQ(particula.c_acc, fuerza);
}

TEST(ParticulaTest, aplicar_fuerza_con_masa_10)
{
    float masa = 10.0f;
    Particula particula(Vector2(), masa);
    Vector2 fuerza(-1.0f, 1.0f);

    particula.aplicar_fuerza(fuerza);

    ASSERT_EQ(particula.c_acc, fuerza / masa);
}

TEST(ParticulaTest, actualizar_particula_sin_fuerza_aplicada_en_delta_tiempo_1)
{
    Particula particula;
    float delta_tiempo = 1.0f;

    particula.actualizar(delta_tiempo);

    ASSERT_EQ(particula.c_pos, Vector2());
    ASSERT_EQ(particula.c_vel, Vector2());
}

TEST(ParticulaTest, actualizar_particula_con_fuerza_aplicada_en_delta_tiempo_1)
{
    Particula particula;
    Vector2 fuerza(10.0f, 30.0f);
    particula.aplicar_fuerza(fuerza);
    float delta_tiempo = 1.0f;

    particula.actualizar(delta_tiempo);

    ASSERT_EQ(particula.c_vel, fuerza);
    ASSERT_EQ(particula.c_pos, particula.c_vel);
}

TEST(ParticulaTest, actualizar_particula_con_fuerza_aplicada_en_delta_tiempo_5)
{
    Particula particula;
    Vector2 fuerza(10.0f, 30.0f);
    particula.aplicar_fuerza(fuerza);
    float delta_tiempo = 5.0f;

    particula.actualizar(delta_tiempo);

    ASSERT_EQ(particula.c_vel, fuerza * delta_tiempo);
    ASSERT_EQ(particula.c_pos, particula.c_vel * delta_tiempo);
}

TEST(ParticulaTest, actualizar_particula_con_posicion_diferente_y_con_fuerza_aplicada_en_delta_tiempo_1)
{
    Vector2 pos_desfase(5.0f, 2.0f);
    Particula particula(pos_desfase);
    Vector2 fuerza(10.0f, 30.0f);
    particula.aplicar_fuerza(fuerza);
    float delta_tiempo = 1.0f;

    particula.actualizar(delta_tiempo);

    ASSERT_EQ(particula.c_vel, fuerza * delta_tiempo);
    ASSERT_EQ(particula.c_pos, particula.c_vel * delta_tiempo + pos_desfase);
}

TEST(ParticulaTest, colision_dos_particulas_con_particulas_intersectando_devuelve_true)
{
    Particula particula1(Vector2(.0f, .0f)), particula2(Vector2(.5f, .5f));
    bool resultado;

    resultado = particula1.colisiona(particula2);

    ASSERT_EQ(resultado, true);
}

TEST(ParticulaTest, colision_dos_particulas_sin_particulas_intersectando_devuelve_false)
{
    Particula particula1(Vector2(-4.0f, -4.0f)), particula2(Vector2(.5f, .5f));
    bool resultado;

    resultado = particula1.colisiona(particula2);

    ASSERT_EQ(resultado, false);
}

TEST(ParticulaTest, colision_dos_particulas_sin_particulas_intersectando_radios_diferentes_devuelve_false)
{
    float radio = 4.0f;
    Particula particula1(Vector2(-4.0f, -4.0f), 1.0f, radio);
    Particula particula2(Vector2(4.5f, 4.5f), 1.0f, radio);
    bool resultado;

    resultado = particula1.colisiona(particula2);

    ASSERT_EQ(resultado, false);
}

TEST(ParticulaTest, colision_dos_particulas_tocandose_bordes_devuelve_true)
{
    Particula particula1(Vector2(-0.0f, -1.0f)), particula2(Vector2(.0f, 1.0f));
    bool resultado;

    resultado = particula1.colisiona(particula2);

    ASSERT_EQ(resultado, true);
}