#include "gtest/gtest.h"
#include "../src/quadtree.h"

class Entidad : public qt::Entidad
{
public:
    CuerpoRigido *m_cuerpo;

public:
    Entidad(CuerpoRigido *cuerpo)
        : m_cuerpo(cuerpo)
    {
    }

    bool colisiona(CuerpoRigido *area)
    {
        return (m_cuerpo->colisiona(area).colisiono);
    }
};

TEST(QuadtreeTest, Entidad_en_rango)
{
    qt::QuadTree qt(Vector2(), 64.0f, 64.0f);

    Circulo circulo(Vector2(), 5.0f);
    Entidad entidad(&circulo);

    ASSERT_TRUE(qt.insertar(&entidad));
}

TEST(QuadtreeTest, Entidad_fuera_de_rango)
{
    qt::QuadTree qt(Vector2(), 64.0f, 64.0f);
    Circulo circulo(Vector2(100.0f, 100.0f), 1.0f);
    Entidad entidad(&circulo);

    ASSERT_FALSE(qt.insertar(&entidad));
}

TEST(QuadtreeTest, Buscar)
{
    qt::QuadTree qt(Vector2(), 64.0f, 64.0f);
    Circulo circulo(Vector2(), 5.0f);
    Entidad entidad(&circulo);

    qt.insertar(&entidad);

    std::vector<qt::Entidad *> buscar = qt.buscar(&circulo);

    for (qt::Entidad *ent : buscar)
        ASSERT_EQ(ent, &entidad);
}

bool hay_entidad(std::vector<qt::Entidad *> lista, qt::Entidad *entidad)
{
    for (qt::Entidad *e : lista)
        if (e == entidad)
            return true;
    return false;
}

TEST(QuadtreeTest, Insertando_5_entidades_para_que_se_subdivida_el_espacio)
{
    AABB area(Vector2(), 64.0f, 64.0f);
    qt::QuadTree qt(area);
    std::vector<qt::Entidad *> entidades;
    std::vector<Circulo *> cuerpos;

    for (float i = 0; i < 5.0f; i++)
    {
        Circulo *c = new Circulo(Vector2(4.0f, 4.0f + i * 8.0f), .0f);
        Entidad *e = new Entidad(c);
        qt.insertar(e);
        entidades.emplace_back(e);
        cuerpos.emplace_back(c);
    }

    std::vector<qt::Entidad *> buscar = qt.buscar(&area);

    ASSERT_EQ(buscar.size(), 5);

    for (qt::Entidad *e : entidades)
        ASSERT_TRUE(hay_entidad(buscar, e));

    for (Circulo *c : cuerpos)
        delete c;
}

TEST(QuadtreeTest, Insertando_5_entidades_todos_tiene_solo_un_padre)
{
    AABB area(Vector2(), 64.0f, 64.0f);
    qt::QuadTree qt(area);
    std::vector<qt::Entidad *> entidades;
    std::vector<Circulo *> cuerpos;

    for (float i = 0; i < 5.0f; i++)
    {
        Circulo *c = new Circulo(Vector2(4.0f, 4.0f + i * 8.0f), .0f);
        Entidad *e = new Entidad(c);
        qt.insertar(e);
        entidades.emplace_back(e);
        cuerpos.emplace_back(c);
    }

    for (qt::Entidad *e : entidades)
        ASSERT_EQ(e->m_padres.size(), 1);

    for (Circulo *c : cuerpos)
        delete c;
}

TEST(QuadtreeTest, Insertar_5_entidades_para_que_no_sea_divisible_y_los_5_tienen_el_mismo_padre)
{
    AABB area(Vector2(), 64.0f, 64.0f);
    qt::QuadTree qt(area);
    std::vector<qt::Entidad *> entidades;
    std::vector<Circulo *> cuerpos;

    for (float i = 0; i < 5.0f; i++)
    {
        Circulo *c = new Circulo(Vector2(), 5.0f);
        Entidad *e = new Entidad(c);
        qt.insertar(e);
        entidades.emplace_back(e);
        cuerpos.emplace_back(c);
    }

    qt::Node *padre = entidades[0]->m_padres[0];
    for (qt::Entidad *e : entidades)
        ASSERT_EQ(e->m_padres[0], padre);

    for (Circulo *c : cuerpos)
        delete c;
}

TEST(QuadtreeTest, Insertando_y_eliminando_una_entidad_en_rango_devuelve_true)
{
    AABB area(Vector2(), 64.0f, 64.0f);
    qt::QuadTree qt(area);
    Circulo circ(Vector2(), 5.0f);
    Entidad ent(&circ);

    qt.insertar(&ent);

    ASSERT_TRUE(qt.eliminar(&ent));
}

TEST(QuadtreeTest, Insertando_y_eliminando_una_entidad_al_buscar_no_hay_entidad)
{
    AABB area(Vector2(), 64.0f, 64.0f);
    qt::QuadTree qt(area);
    Circulo circ(Vector2(), 5.0f);
    Entidad ent(&circ);

    qt.insertar(&ent);
    qt.eliminar(&ent);

    std::vector<qt::Entidad *> buscar = qt.buscar(&area);

    ASSERT_EQ(buscar.size(), 0);
}

TEST(QuadtreeTest, Insertando_y_eliminando_5_entidades_al_buscar_no_hay_entidades)
{
    AABB area(Vector2(), 64.0f, 64.0f);
    qt::QuadTree qt(area);
    std::vector<qt::Entidad *> entidades;
    std::vector<Circulo *> cuerpos;

    for (float i = 0; i < 5.0f; i++)
    {
        Circulo *c = new Circulo(Vector2(4.0f, 4.0f + i * 8.0f), .0f);
        Entidad *e = new Entidad(c);
        qt.insertar(e);
        entidades.emplace_back(e);
        cuerpos.emplace_back(c);
    }

    for (qt::Entidad *e : entidades)
        qt.eliminar(e);

    std::vector<qt::Entidad *> buscar = qt.buscar(&area);

    ASSERT_EQ(buscar.size(), 0);

    for (Circulo *c : cuerpos)
        delete c;
}

TEST(QuadtreeTest, Insertando_y_eliminando_5_entidades_y_no_tiene_padres)
{
    AABB area(Vector2(), 64.0f, 64.0f);
    qt::QuadTree qt(area);
    std::vector<qt::Entidad *> entidades;
    std::vector<Circulo *> cuerpos;

    for (float i = 0; i < 5.0f; i++)
    {
        Circulo *c = new Circulo(Vector2(4.0f, 4.0f + i * 8.0f), .0f);
        Entidad *e = new Entidad(c);
        qt.insertar(e);
        entidades.emplace_back(e);
        cuerpos.emplace_back(c);
    }

    for (qt::Entidad *e : entidades)
    {
        qt.eliminar(e);
        ASSERT_TRUE(e->m_padres.empty());
    }

    for (Circulo *c : cuerpos)
        delete c;
}

TEST(QuadtreeTest, Muesto_una_entidad_y_la_actualizo_y_busco_en_la_zona_nueva)
{
    AABB area(Vector2(), 64.0f, 64.0f);
    qt::QuadTree qt(area);
    Circulo circ(Vector2(), 5.0f);
    Entidad ent(&circ);

    qt.insertar(&ent);
    circ.m_posicion = Vector2(20.0f, 20.0f);
    qt.actualizar(&ent);

    AABB area_busqueda(Vector2(20.0f, 20.0f), 10.0f, 10.0f);
    std::vector<qt::Entidad *> buscar = qt.buscar(&area_busqueda);

    ASSERT_EQ(buscar.size(), 1);
}

TEST(QuadtreeTest, Varias_entidades_para_tener_una_subdivison_y_actualizo_una_particula_y_busco_en_la_zona_nueva)
{
    AABB area(Vector2(), 64.0f, 64.0f);
    qt::QuadTree qt(area);
    std::vector<qt::Entidad *> entidades;
    std::vector<Circulo *> cuerpos;

    for (float i = 0; i < 5.0f; i++)
    {
        Circulo *c = new Circulo(Vector2(-48.0f, -54.0f + i * 2.0f), 2.0f);
        Entidad *e = new Entidad(c);
        qt.insertar(e);
        entidades.emplace_back(e);
        cuerpos.emplace_back(c);
    }

    cuerpos[0]->m_posicion = Vector2(32.0f, 32.0f);
    qt.actualizar(entidades[0]);

    AABB area_busqueda(Vector2(32.0f, 32.0f), 20.0f, 20.0f);
    std::vector<qt::Entidad *> buscar = qt.buscar(&area_busqueda);

    ASSERT_EQ(buscar.size(), 1);
}
