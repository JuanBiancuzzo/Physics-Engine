#include "gtest/gtest.h"
#include "../src/cuerpos/gjk.h"

using namespace cr;

TEST(CuerposTest, Colision_entre_aabb_y_aabb_fuera_de_rango)
{
    AABB rect(Vector2(-4.0f, -3.5f), 3.0f, 1.5f);
    AABB rect2(Vector2(4.0f, 2.0f), 2.0f, 2.0f);
    bool colicion_rr2 = rect.colisiona(&rect2);
    bool colicion_r2r = rect2.colisiona(&rect);

    ASSERT_FALSE(colicion_r2r);
    ASSERT_FALSE(colicion_rr2);
}

TEST(CuerposTest, Colision_entre_aabb_y_aabb_en_rango)
{
    AABB rect(Vector2(1.0f, 1.0f), 2.0f, 2.0f);
    AABB rect2(Vector2(4.0f, 2.0f), 2.0f, 2.0f);
    bool colicion_rr2 = rect.colisiona(&rect2);
    bool colicion_r2r = rect2.colisiona(&rect);

    ASSERT_TRUE(colicion_r2r);
    ASSERT_TRUE(colicion_rr2);
}

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

TEST(CuerposTest, Direccion_de_colision_entre_un_circulo_centro_y_arriba_de_un_aabb_es_hacia_abajo)
{
    Circulo circulo(Vector2(.0f, 1.0f), 1.0f);
    AABB rect(Vector2(.0f, -1.0f), 10.0f, 1.0f);

    PuntoDeColision pdc = circulo.punto_de_colision(&rect);
    ASSERT_EQ(pdc.normal, Vector2(.0f, -1.0f));
}

TEST(CuerposTest, Direccion_de_colision_entre_un_circulo_no_centro_y_arriba_de_un_aabb_es_hacia_abajo)
{
    Circulo circulo(Vector2(3.0f, 1.0f), 1.0f);
    AABB rect(Vector2(.0f, -1.0f), 10.0f, 1.0f);

    PuntoDeColision pdc = circulo.punto_de_colision(&rect);
    ASSERT_EQ(pdc.normal, Vector2(.0f, -1.0f));
}

TEST(CuerposTest, Direccion_de_colision_entre_un_circulo_centro_y_arriba_de_una_linea_es_hacia_abajo)
{
    Circulo circulo(Vector2(.0f, 1.0f), 1.0f);
    Poligono<2> linea({Vector2(-10.0f, .0f), Vector2(10.0f, .0f)});

    PuntoDeColision pdc = circulo.punto_de_colision(&linea);
    ASSERT_EQ(pdc.normal, Vector2(.0f, -1.0f));
}

TEST(CuerposTest, Direccion_de_colision_entre_un_circulo_no_centro_y_arriba_de_una_linea_es_hacia_abajo)
{
    Circulo circulo(Vector2(3.0f, 1.0f), 1.0f);
    Poligono<2> linea({Vector2(10.0f, .0f), Vector2(-10.0f, .0f)});

    PuntoDeColision pdc = circulo.punto_de_colision(&linea);
    ASSERT_EQ(pdc.normal, Vector2(.0f, -1.0f));
}

TEST(CuerposTest, Direccion_de_colision_entre_un_circulo_no_centro_y_metido_en_la_linea_y_arriba_de_una_linea_es_hacia_abajo)
{
    Circulo circulo(Vector2(.0f, .0f), 1.0f);
    Poligono<2> linea({Vector2(10.0f, .0f), Vector2(-10.0f, .0f)});

    PuntoDeColision pdc = circulo.punto_de_colision(&linea);
    ASSERT_EQ(pdc.normal, Vector2(.0f, .0f));
}

TEST(CuerposTest, Direccion_de_colision_entre_dos_circulos_uno_al_lado_del_otro)
{
    Circulo circulo1(Vector2(-1.0f, .0f), 1.0f);
    Circulo circulo2(Vector2(1.0f, .0f), 1.0f);

    PuntoDeColision pdc = circulo1.punto_de_colision(&circulo2);
    ASSERT_TRUE(pdc.colisiono);
    ASSERT_EQ(pdc.normal, Vector2(1.0f, .0f));
}

TEST(CuerposTest, Direccion_de_colision_entre_un_circulo_centro_y_un_aabb_es_hacia_la_derecha)
{
    Circulo circulo(Vector2(.0f, .0f), 1.0f);
    AABB rect(Vector2(2.0f, .0f), 1.0f, 1.0f);

    PuntoDeColision pdc = circulo.punto_de_colision(&rect);
    ASSERT_EQ(pdc.normal, Vector2(1.0f, .0f));
}

TEST(CuerposTest, Direccion_de_colision_entre_dos_aabb_es_hacia_la_derecha)
{
    AABB rect1(Vector2(.0f, .0f), 1.0f, 1.0f);
    AABB rect2(Vector2(2.0f, .0f), 1.0f, 1.0f);

    PuntoDeColision pdc = rect1.punto_de_colision(&rect2);
    ASSERT_EQ(pdc.normal, Vector2(1.0f, .0f));
}