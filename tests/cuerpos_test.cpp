#include "gtest/gtest.h"
#include "../src/cuerpos/gjk.h"

using namespace cr;

TEST(CuerposTest, Colision_entre_circulo_y_aabb_en_rango)
{
    AABB rect(Vector2(), 64.0f, 64.0f);
    Circulo circulo(Vector2(10.0f, 10.0f), 1.0f);
    bool colicion_cr = circulo.colisiona(&rect);
    bool colicion_rc = rect.colisiona(&circulo);

    ASSERT_TRUE(colicion_cr);
    ASSERT_TRUE(colicion_rc);
}

TEST(CuerposTest, Colision_entre_circulo_y_aabb_en_rango_y_estan_en_la_misma_posicion)
{
    AABB rect(Vector2(), 64.0f, 64.0f);
    Circulo circulo(Vector2(), 1.0f);
    bool colicion_cr = circulo.colisiona(&rect);
    bool colicion_rc = rect.colisiona(&circulo);

    ASSERT_TRUE(colicion_cr);
    ASSERT_TRUE(colicion_rc);
}

TEST(CuerposTest, Colision_entre_circulo_y_aabb_en_rango_y_estan_en_la_misma_posicion_sin_ser_el_cero_cero)
{
    AABB rect(Vector2(45.0f, 34.0f), 64.0f, 64.0f);
    Circulo circulo(Vector2(45.0f, 34.0f), 1.0f);
    bool colicion_cr = circulo.colisiona(&rect);
    bool colicion_rc = rect.colisiona(&circulo);

    ASSERT_TRUE(colicion_cr);
    ASSERT_TRUE(colicion_rc);
}

TEST(CuerposTest, Colision_entre_circulo_y_aabb_fuera_de_rango)
{
    AABB rect(Vector2(1.0f, .0f), 64.0f, 64.0f);
    Circulo circulo(Vector2(100.0f, 100.0f), 1.0f);
    bool colicion_cr = circulo.colisiona(&rect);
    bool colicion_rc = rect.colisiona(&circulo);

    ASSERT_FALSE(colicion_cr);
    ASSERT_FALSE(colicion_rc);
}

TEST(CuerposTest, Colision_entre_circulo_y_aabb_fuera_de_rango_en_una_diagonal)
{
    AABB rect(Vector2(.0f, .0f), 64.0f, 64.0f);
    Circulo circulo(Vector2(100.0f, -100.0f), 1.0f);
    bool colicion_cr = circulo.colisiona(&rect);
    bool colicion_rc = rect.colisiona(&circulo);

    ASSERT_FALSE(colicion_cr);
    ASSERT_FALSE(colicion_rc);
}

TEST(CuerposTest, Colision_entre_circulo_de_radio_nulo_y_aabb_en_fuera_de_rango_pero_pasa_algo_raro)
{
    AABB rect(Vector2(.0f, .0f), 64.0f, 64.0f);
    Circulo circulo(Vector2(4.0f, 20.0f), .0f);
    bool colicion_cr = circulo.colisiona(&rect);
    bool colicion_rc = rect.colisiona(&circulo);

    ASSERT_TRUE(colicion_cr);
    ASSERT_TRUE(colicion_rc);
}

TEST(CuerposTest, Colision_entre_circulo_y_aabb_y_apenas_se_tocan_y_es_valido)
{
    AABB rect(Vector2(), 10.0f, 10.0f);
    Circulo circulo(Vector2(20.0f, .0f), 10.0f);
    bool colicion_cr = circulo.colisiona(&rect);
    bool colicion_rc = rect.colisiona(&circulo);

    ASSERT_TRUE(colicion_cr);
    ASSERT_TRUE(colicion_rc);
}

TEST(CuerposTest, Colision_entre_circulo_de_radio_nulo_y_aabb_y_apenas_se_tocan_y_es_valido)
{
    AABB rect(Vector2(), 10.0f, 10.0f);
    Circulo circulo(Vector2(10.0f, .0f), .0f);
    bool colicion_cr = circulo.colisiona(&rect);
    bool colicion_rc = rect.colisiona(&circulo);

    ASSERT_TRUE(colicion_cr);
    ASSERT_TRUE(colicion_rc);
}

TEST(CuerposTest, Colision_entre_circulo_de_radio_nulo_y_aabb_y_estan_puestos_en_el_mismo_lugar)
{
    AABB rect(Vector2(), 10.0f, 10.0f);
    Circulo circulo(Vector2(), .0f);
    bool colicion_cr = circulo.colisiona(&rect);
    bool colicion_rc = rect.colisiona(&circulo);

    ASSERT_TRUE(colicion_cr);
    ASSERT_TRUE(colicion_rc);
}
