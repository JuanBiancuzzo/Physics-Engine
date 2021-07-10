#include "gtest/gtest.h"
#include "../src/cuerpos/gjk.h"

TEST(CuerposTest, Colision_entre_circulo_y_aabb_en_rango)
{
    AABB rect(Vector2(), 10.0f, 10.0f);
    Circulo circulo(Vector2(), 10.0f);
    PuntoDeColision punto_de_colision = circulo.colisiona(&rect);

    ASSERT_TRUE(punto_de_colision.colisiono);
}

TEST(CuerposTest, Colision_entre_circulo_de_radio_cero_y_aabb_en_rango)
{
    AABB rect(Vector2(), 10.0f, 10.0f);
    Circulo circulo(Vector2(), .0f);
    PuntoDeColision punto_de_colision = circulo.colisiona(&rect);

    ASSERT_TRUE(punto_de_colision.colisiono);
}

TEST(CuerposTest, Colision_entre_circulo_y_aabb_fuera_de_rango)
{
    AABB rect(Vector2(), 10.0f, 10.0f);
    Circulo circulo(Vector2(100.0f, .0f), 10.0f);
    PuntoDeColision punto_de_colision = circulo.colisiona(&rect);

    ASSERT_FALSE(punto_de_colision.colisiono);
}

TEST(CuerposTest, Colision_entre_circulo_y_aabb_y_apenas_se_tocan_y_es_valido)
{
    AABB rect(Vector2(), 10.0f, 10.0f);
    Circulo circulo(Vector2(20.0f, .0f), 10.0f);
    PuntoDeColision punto_de_colision = circulo.colisiona(&rect);

    ASSERT_TRUE(punto_de_colision.colisiono);
}
