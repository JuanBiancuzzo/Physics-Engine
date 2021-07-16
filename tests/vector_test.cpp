#include "gtest/gtest.h"
#include "../src/vector2.h"

#include <math.h>

TEST(VectorTest, Inicializar_vector_sin_parametros)
{
    Vector2 vector;

    ASSERT_EQ(vector.x, .0f);
    ASSERT_EQ(vector.y, .0f);
}

TEST(VectorTest, Inicializar_vector_con_parametros)
{
    float x = 4.0f, y = -3.0f;
    Vector2 vector(x, y);

    ASSERT_EQ(vector.x, x);
    ASSERT_EQ(vector.y, y);
}

TEST(VectorTest, Suma_de_vectores)
{
    Vector2 vector1(0.4f, 6.3f), vector2(3.4f, 7.4f);
    Vector2 resultado;

    resultado = vector1 + vector2;

    ASSERT_EQ(resultado.x, vector1.x + vector2.x);
    ASSERT_EQ(resultado.y, vector1.y + vector2.y);
}

TEST(VectorTest, Resta_de_vectores)
{
    Vector2 vector1(0.4f, -5.3f), vector2(-3.4f, 4.4f);
    Vector2 resultado;

    resultado = vector1 - vector2;

    ASSERT_EQ(resultado.x, vector1.x - vector2.x);
    ASSERT_EQ(resultado.y, vector1.y - vector2.y);
}

TEST(VectorTest, Multiplicacion_de_un_vector_con_un_escalar)
{
    Vector2 vector(4.3f, -1.3f);
    float escalar = -43.0f;
    Vector2 resultado;

    resultado = vector * escalar;

    ASSERT_EQ(resultado.x, vector.x * escalar);
    ASSERT_EQ(resultado.y, vector.y * escalar);
}

TEST(VectorTest, Multiplicacion_de_un_vector_con_otro_vector)
{
    Vector2 vector1(0.4f, -5.3f), vector2(-3.4f, 4.4f);
    float resultado;

    resultado = vector1 * vector2;

    ASSERT_EQ(resultado, vector1.x * vector2.x + vector1.y * vector2.y);
}

TEST(VectorTest, Division_de_un_vector_con_un_escalar)
{
    Vector2 vector(42.3f, -61.7f);
    float escalar = 3.4f;
    Vector2 resultado;

    resultado = vector / escalar;

    ASSERT_EQ(resultado.x, vector.x / escalar);
    ASSERT_EQ(resultado.y, vector.y / escalar);
}

TEST(VectorTest, Suma_igual_de_un_vector)
{
    Vector2 vector1(0.4f, 6.3f), vector2(3.4f, 7.4f);
    Vector2 aux = vector1;

    vector1 += vector2;

    ASSERT_EQ(vector1.x, aux.x + vector2.x);
    ASSERT_EQ(vector1.y, aux.y + vector2.y);
}

TEST(VectorTest, Resta_igual_de_un_vector)
{
    Vector2 vector1(0.4f, 6.3f), vector2(3.4f, 7.4f);
    Vector2 aux = vector1;

    vector1 -= vector2;

    ASSERT_EQ(vector1.x, aux.x - vector2.x);
    ASSERT_EQ(vector1.y, aux.y - vector2.y);
}

TEST(VectorTest, Multiplicacion_igual_de_un_vector_con_un_escalar)
{
    Vector2 vector(42.3f, -61.7f);
    float escalar = 3.4f;
    Vector2 aux = vector;

    vector *= escalar;

    ASSERT_EQ(vector.x, aux.x * escalar);
    ASSERT_EQ(vector.y, aux.y * escalar);
}

TEST(VectorTest, Division_igual_de_un_vector_con_un_escalar)
{
    Vector2 vector(42.3f, -61.7f);
    float escalar = 3.4f;
    Vector2 aux = vector;

    vector /= escalar;

    ASSERT_EQ(vector.x, aux.x / escalar);
    ASSERT_EQ(vector.y, aux.y / escalar);
}

TEST(VectorTest, Comparasion_de_dos_vectores_iguales_devuelve_true)
{
    Vector2 vector1(42.3f, -61.7f), vector2(42.3f, -61.7f);
    bool resultado;

    resultado = vector1 == vector2;

    ASSERT_EQ(resultado, true);
}

TEST(VectorTest, Comparasion_de_dos_vectores_diferentes_devuelve_false)
{
    Vector2 vector1(42.3f, -61.7f), vector2(4.3f, -631.7f);
    bool resultado;

    resultado = vector1 == vector2;

    ASSERT_EQ(resultado, false);
}

TEST(VectorTest, calcular_el_modulo_de_un_vector)
{
    Vector2 vector(3.0f, 4.0f);

    float resultado = vector.modulo();

    ASSERT_EQ(resultado, 5.0f);
}

TEST(VectorTest, calcular_el_modulo_cuadrado_de_un_vector)
{
    Vector2 vector(3.0f, 4.0f);

    float resultado = vector.modulo_cuadrado();

    ASSERT_EQ(resultado, 25.0f);
}

TEST(VectorTest, calcular_distancia_entre_vectores)
{
    Vector2 vector1(0.4f, 6.3f), vector2(3.4f, 7.4f);
    float resultado;

    resultado = vector1.distancia(vector2);

    ASSERT_EQ(resultado, (vector1 - vector2).modulo());
}

TEST(VectorTest, calcular_distancia_cuadrada_entre_vectores)
{
    Vector2 vector1(0.4f, 6.3f), vector2(3.4f, 7.4f);
    float resultado;

    resultado = vector1.distancia_cuadrada(vector2);

    float esperado = ((vector1.x - vector2.x) * (vector1.x - vector2.x) + (vector1.y - vector2.y) * (vector1.y - vector2.y));

    ASSERT_EQ(resultado, esperado);
}

TEST(VectorTest, calcular_la_proyeccion_sobre_el_eje_x)
{
    Vector2 vector(31.4f, 45.3f), versor_x(1.0f, .0f);
    Vector2 resultado;

    resultado = vector.proyeccion(versor_x);

    ASSERT_EQ(resultado.x, vector.x);
    ASSERT_EQ(resultado.y, 0.0f);
}

TEST(VectorTest, calcular_la_proyeccion_sobre_el_eje_y)
{
    Vector2 vector(31.4f, 45.3f), versor_y(.0f, 1.0f);
    Vector2 resultado;

    resultado = vector.proyeccion(versor_y);

    ASSERT_EQ(resultado.x, .0f);
    ASSERT_EQ(resultado.y, vector.y);
}

TEST(VectorTest, calcular_la_normal_de_un_vector)
{
    Vector2 vector(31.4f, 45.3f);
    Vector2 resultado;

    resultado = vector.normal();
    float x = vector.x / (sqrt(pow(vector.x, 2) + pow(vector.y, 2)));
    float y = vector.y / (sqrt(pow(vector.x, 2) + pow(vector.y, 2)));

    ASSERT_NEAR(resultado.x, x, 0.01f);
    ASSERT_NEAR(resultado.y, y, 0.01f);
}