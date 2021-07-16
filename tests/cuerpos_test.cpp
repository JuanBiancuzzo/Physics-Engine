#include "gtest/gtest.h"
#include "../src/cuerpos/gjk.h"

TEST(CuerposTest, Colision_entre_circulo_y_aabb_en_rango)
{
    AABB rect(Vector2(), 64.0f, 64.0f);
    Circulo circulo(Vector2(10.0f, 10.0f), 1.0f);
    PuntoDeColision punto_de_colision_cr = circulo.colisiona(&rect);
    PuntoDeColision punto_de_colision_rc = rect.colisiona(&circulo);

    ASSERT_TRUE(punto_de_colision_cr.colisiono);
    ASSERT_TRUE(punto_de_colision_rc.colisiono);
}

TEST(CuerposTest, Colision_entre_circulo_y_aabb_en_rango_y_estan_en_la_misma_posicion)
{
    AABB rect(Vector2(), 64.0f, 64.0f);
    Circulo circulo(Vector2(), 1.0f);
    PuntoDeColision punto_de_colision_cr = circulo.colisiona(&rect);
    PuntoDeColision punto_de_colision_rc = rect.colisiona(&circulo);

    ASSERT_TRUE(punto_de_colision_cr.colisiono);
    ASSERT_TRUE(punto_de_colision_rc.colisiono);
}

TEST(CuerposTest, Colision_entre_circulo_y_aabb_fuera_de_rango)
{
    AABB rect(Vector2(), 64.0f, 64.0f);
    Circulo circulo(Vector2(100.0f, 100.0f), 1.0f);
    PuntoDeColision punto_de_colision_cr = circulo.colisiona(&rect);
    PuntoDeColision punto_de_colision_rc = rect.colisiona(&circulo);

    ASSERT_FALSE(punto_de_colision_cr.colisiono);
    ASSERT_FALSE(punto_de_colision_rc.colisiono);
}

TEST(CuerposTest, Colision_entre_circulo_y_aabb_y_apenas_se_tocan_y_es_valido)
{
    AABB rect(Vector2(), 10.0f, 10.0f);
    Circulo circulo(Vector2(20.0f, .0f), 10.0f);
    PuntoDeColision punto_de_colision_cr = circulo.colisiona(&rect);
    PuntoDeColision punto_de_colision_rc = rect.colisiona(&circulo);

    ASSERT_TRUE(punto_de_colision_cr.colisiono);
    ASSERT_TRUE(punto_de_colision_rc.colisiono);
}

TEST(CuerposTest, Colision_entre_circulo_de_radio_nulo_y_aabb_y_apenas_se_tocan_y_es_valido)
{
    AABB rect(Vector2(), 10.0f, 10.0f);
    Circulo circulo(Vector2(10.0f, .0f), .0f);
    PuntoDeColision punto_de_colision_cr = circulo.colisiona(&rect);
    PuntoDeColision punto_de_colision_rc = rect.colisiona(&circulo);

    ASSERT_TRUE(punto_de_colision_cr.colisiono);
    ASSERT_TRUE(punto_de_colision_rc.colisiono);
}

TEST(CuerposTest, Colision_entre_circulo_de_radio_nulo_y_aabb_y_estan_puestos_en_el_mismo_lugar)
{
    AABB rect(Vector2(), 10.0f, 10.0f);
    Circulo circulo(Vector2(), .0f);
    PuntoDeColision punto_de_colision_cr = circulo.colisiona(&rect);
    PuntoDeColision punto_de_colision_rc = rect.colisiona(&circulo);

    ASSERT_TRUE(punto_de_colision_cr.colisiono);
    ASSERT_TRUE(punto_de_colision_rc.colisiono);
}
