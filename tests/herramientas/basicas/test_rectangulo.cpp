#include "gtest/gtest.h"
#include "../../../src/herramientas/basicas/rectangulo.h"

TEST(RectanguloTest, Inicializar_rectangulo_sin_parametros)
{
    Rectangulo rectangulo;

    ASSERT_EQ(rectangulo.c_pos.x, .0f);
    ASSERT_EQ(rectangulo.c_pos.y, .0f);
    ASSERT_EQ(rectangulo.c_w, 1.0f);
    ASSERT_EQ(rectangulo.c_h, 1.0f);
}

TEST(RectanguloTest, Inicializar_rectangulo_con_posicion)
{
    Vector2 pos(5.23f, 45.3f);
    Rectangulo rectangulo(pos);

    ASSERT_EQ(rectangulo.c_pos.x, pos.x);
    ASSERT_EQ(rectangulo.c_pos.y, pos.y);
    ASSERT_EQ(rectangulo.c_w, 1.0f);
    ASSERT_EQ(rectangulo.c_h, 1.0f);
}

TEST(RectanguloTest, Inicializar_rectangulo_con_posicion_ancho_y_alto)
{
    Vector2 pos(5.23f, 45.3f);
    float w = 42.5f, h = 34.23f;
    Rectangulo rectangulo(pos, w, h);

    ASSERT_EQ(rectangulo.c_pos.x, pos.x);
    ASSERT_EQ(rectangulo.c_pos.y, pos.y);
    ASSERT_EQ(rectangulo.c_w, w);
    ASSERT_EQ(rectangulo.c_h, h);
}

TEST(RectanguloTest, Funcion_contiene_entidad_con_entidad_adentro_devuelve_true)
{
    Entidad e;
    Rectangulo rect(Vector2(5.0f, 5.0f), 10.0f, 10.0f);
    bool resultado;

    resultado = rect.contiene(e);

    ASSERT_EQ(resultado, true);
}

TEST(RectanguloTest, Funcion_contiene_entidad_con_entidad_afuera_devuelve_false)
{
    Entidad e(Vector2(-30.0f, -30.0f));
    Rectangulo rect(Vector2(5.0f, 5.0f), 10.0f, 10.0f);
    bool resultado;

    resultado = rect.contiene(e);

    ASSERT_EQ(resultado, false);
}

TEST(RectanguloTest, Funcion_contiene_entidad_con_entidad_en_el_borde_devuelve_true)
{
    Entidad e(Vector2(10.0f, 10.0f));
    Rectangulo rect(Vector2(), 10.0f, 10.0f);
    bool resultado;

    resultado = rect.contiene(e);

    ASSERT_EQ(resultado, true);
}

TEST(RectanguloTest, Funcion_intersecta_con_rectangulo_adentro_devuelve_true)
{
    Rectangulo rect(Vector2(5.0f, 5.0f), 10.0f, 10.0f);
    Rectangulo frontera(Vector2(15.0f, 15.0f), 10.0f, 10.0f);
    bool resultado;

    resultado = rect.intersecta(frontera);

    ASSERT_EQ(resultado, true);
}

TEST(RectanguloTest, Funcion_intersecta_con_rectangulo_afuera_devuelve_false)
{
    Rectangulo rect(Vector2(5.0f, 5.0f), 10.0f, 10.0f);
    Rectangulo frontera(Vector2(40.0f, 40.0f), 10.0f, 10.0f);
    bool resultado;

    resultado = rect.intersecta(frontera);

    ASSERT_EQ(resultado, false);
}

TEST(RectanguloTest, Funcion_intersecta_con_rectangulo_en_el_borde_devuelve_false)
{
    Rectangulo rect(Vector2(5.0f, 5.0f), 10.0f, 10.0f);
    Rectangulo frontera(Vector2(25.0f, 5.0f), 10.0f, 10.0f);
    bool resultado;

    resultado = rect.intersecta(frontera);

    ASSERT_EQ(resultado, false);
}