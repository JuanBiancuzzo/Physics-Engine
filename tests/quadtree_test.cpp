#include "gtest/gtest.h"
#include "../src/quadtree.h"

TEST(QuadtreeTest, Entidad_en_rango)
{
    QuadTree qt(Vector2(), 64.0f, 64.0f);
    Circulo circulo(Vector2(), 5.0f);
    Entidad entidad(&circulo);

    ASSERT_TRUE(qt.insertar(&entidad));
}

TEST(QuadtreeTest, Entidad_fuera_de_rango)
{
    QuadTree qt(Vector2(), 64.0f, 64.0f);
    Circulo circulo(Vector2(100.0f, 100.0f), 1.0f);
    Entidad entidad(&circulo);

    ASSERT_FALSE(qt.insertar(&entidad));
}

TEST(QuadtreeTest, Buscar)
{
    QuadTree qt(Vector2(), 64.0f, 64.0f);
    Circulo circulo(Vector2(), 5.0f);
    Entidad entidad(&circulo);

    qt.insertar(&entidad);

    std::vector<Entidad *> buscar = qt.buscar(&circulo);

    for (Entidad *ent : buscar)
        ASSERT_EQ(ent, &entidad);
}

bool hay_entidad(std::vector<Entidad *> lista, Entidad *entidad)
{
    for (Entidad *e : lista)
        if (e == entidad)
            return true;
    return false;
}

TEST(QuadtreeTest, Insertando_5_entidades_para_que_se_subdivida_el_espacio)
{
    AABB area(Vector2(), 64.0f, 64.0f);
    QuadTree qt(area);

    Circulo c1(Vector2(4.0f, 4.0f), .0f);
    Entidad e1(&c1);
    qt.insertar(&e1);
    Circulo c2(Vector2(4.0f, 12.0f), .0f);
    Entidad e2(&c2);
    qt.insertar(&e2);
    Circulo c3(Vector2(4.0f, 20.0f), .0f);
    Entidad e3(&c3);
    qt.insertar(&e3);
    Circulo c4(Vector2(4.0f, 28.0f), .0f);
    Entidad e4(&c4);
    qt.insertar(&e4);
    Circulo c5(Vector2(4.0f, 32.0f), .0f);
    Entidad e5(&c5);
    qt.insertar(&e5);

    std::vector<Entidad *> buscar = qt.buscar(&area);

    ASSERT_EQ(buscar.size(), 5);

    ASSERT_TRUE(hay_entidad(buscar, &e1));
    ASSERT_TRUE(hay_entidad(buscar, &e2));
    ASSERT_TRUE(hay_entidad(buscar, &e3));
    ASSERT_TRUE(hay_entidad(buscar, &e4));
    ASSERT_TRUE(hay_entidad(buscar, &e5));
}