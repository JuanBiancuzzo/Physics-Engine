#include "gtest/gtest.h"
#include "../src/sistema.h"

using namespace sistema;

void velocidades(std::vector<Particula *> particulas)
{
    std::cout << "Velocidades" << std::endl;
    for (Particula *particula : particulas)
        std::cout << "Particula: x = " << particula->m_velocidad.x << ", y = " << particula->m_velocidad.y << std::endl;
}

TEST(SistemaTest, Dos_particulas_y_el_piso_sin_velocidad_ninguna_sus_fuerzas_finales_son_cero)
{
    std::vector<Particula *> particulas;
    Particula *particula1 = new Particula(1.0f, Vector2(), Vector2(.0f, -10.0f), 1.0f);
    Particula *particula2 = new Particula(2.0f, Vector2(), Vector2(.0f, -20.0f), 1.0f);
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

    ASSERT_EQ(particula1->m_velocidad, Vector2());
    ASSERT_EQ(particula2->m_velocidad, Vector2());

    for (Particula *p : particulas)
        delete p;
}

TEST(SistemaTest, Dos_particulas_y_el_piso_el_primero_con_velocidad_y_rebota_con_su_velocidad_invertida)
{
    std::vector<Particula *> particulas;
    Particula *particula1 = new Particula(1.0f, Vector2(.0f, -10.0f), Vector2(.0f, -10.0f), 1.0f);
    Particula *particula2 = new Particula(2.0f, Vector2(), Vector2(.0f, -20.0f), 1.0f);
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

    ASSERT_EQ(particula1->m_velocidad, Vector2(.0f, 7.777f));
    ASSERT_EQ(particula2->m_velocidad, Vector2(.0f, 4.444f));

    for (Particula *p : particulas)
        delete p;
}

TEST(SistemaTest, Dos_particulas_sobre_el_piso_una_tiene_velocidad_y_terminan_intercambiando_velocidades)
{
    std::vector<Particula *> particulas;
    Particula *particula1 = new Particula(1.0f, Vector2(10.0f, .0f), Vector2(.0f, -10.0f), 1.0f);
    Particula *particula2 = new Particula(1.0f, Vector2(), Vector2(.0f, -10.0f), 1.0f);
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
    ASSERT_EQ(particula2->m_velocidad, Vector2(10.0f, .0f));

    for (Particula *p : particulas)
        delete p;
}

TEST(SistemaTest, Dos_particulas_sobre_el_piso_una_tienen_velocidades_y_hay_un_choque_elastico)
{
    std::vector<Particula *> particulas;
    Particula *particula1 = new Particula(1.0f, Vector2(30.0f, .0f), Vector2(.0f, -10.0f), 1.0f);
    Particula *particula2 = new Particula(2.0f, Vector2(-30.0f, .0f), Vector2(.0f, -20.0f), 1.0f);
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
    ASSERT_EQ(particula2->m_velocidad, Vector2(10.0f, .0f));

    for (Particula *p : particulas)
        delete p;
}

TEST(SistemaTest, Particula_estando_en_una_esquina_y_una_velocidad_horizontal_rebota_contra_la_pared)
{
    std::vector<Particula *> particulas;
    Particula *particula = new Particula(1.0f, Vector2(10.0f, .0f), Vector2(.0f, -10.0f), 1.0f);
    Particula *piso = new Particula();
    Particula *pared = new Particula();

    particulas.emplace_back(particula);
    particulas.emplace_back(piso);
    particulas.emplace_back(pared);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_abajo(.0f, -1.0f), dir_arriba(.0f, 1.0f), dir_derecha(1.0f, .0f), dir_izquierda(-1.0f, .0f);
    sistema.agregar_interaccion(particula, piso, dir_abajo);
    sistema.agregar_interaccion(piso, particula, dir_arriba);
    sistema.agregar_interaccion(particula, pared, dir_derecha);
    sistema.agregar_interaccion(pared, particula, dir_izquierda);

    sistema.expandir_fuerzas();

    ASSERT_EQ(particula->m_velocidad, Vector2(-10.0f, .0f));

    for (Particula *p : particulas)
        delete p;
}

TEST(SistemaTest, Particula_choca_contra_el_piso_con_una_velocidad_y_rebota_terminando_con_la_velocidad_opuesta)
{
    std::vector<Particula *> particulas;
    Particula *particula = new Particula(1.0f, Vector2(.0f, -10.0f), Vector2(.0f, -10.0f), 1.0f);
    Particula *piso = new Particula();

    particulas.emplace_back(particula);
    particulas.emplace_back(piso);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_abajo(.0f, -1.0f), dir_arriba(.0f, 1.0f);
    sistema.agregar_interaccion(particula, piso, dir_abajo);
    sistema.agregar_interaccion(piso, particula, dir_arriba);

    sistema.expandir_fuerzas();

    ASSERT_EQ(particula->m_velocidad, Vector2(.0f, 10.0f));

    for (Particula *p : particulas)
        delete p;
}

TEST(SistemaTest, Dos_particulas_con_velocidades_en_la_misma_direccion_pero_hay_choque)
{
    std::vector<Particula *> particulas;
    Particula *particula1 = new Particula(1.0f, Vector2(.0f, 10.0f / 3.0f), Vector2(.0f, .0f), 1.0f);
    Particula *particula2 = new Particula(2.0f, Vector2(.0f, 20.0f / 3.0f), Vector2(.0f, .0f), 1.0f);

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_abajo(.0f, -1.0f), dir_arriba(.0f, 1.0f);
    sistema.agregar_interaccion(particula2, particula1, dir_arriba);
    sistema.agregar_interaccion(particula1, particula2, dir_abajo);

    sistema.expandir_fuerzas();

    ASSERT_EQ(particula1->m_velocidad, Vector2(.0f, 7.77f));
    ASSERT_EQ(particula2->m_velocidad, Vector2(.0f, 4.44f));

    for (Particula *p : particulas)
        delete p;
}

TEST(SistemaTest, Simular_el_pendulo_de_newton_con_todas_las_particulas_de_la_misma_masa)
{
    std::vector<Particula *> particulas;
    Particula *particula1 = new Particula(1.0f, Vector2(10.0f, .0f), Vector2(.0f, -10.0f), 1.0f);
    Particula *particula2 = new Particula(1.0f, Vector2(.0f, .0f), Vector2(.0f, -10.0f), 1.0f);
    Particula *particula3 = new Particula(1.0f, Vector2(.0f, .0f), Vector2(.0f, -10.0f), 1.0f);
    Particula *particula4 = new Particula(1.0f, Vector2(.0f, .0f), Vector2(.0f, -10.0f), 1.0f);
    Particula *particula5 = new Particula(1.0f, Vector2(.0f, .0f), Vector2(.0f, -10.0f), 1.0f);
    Particula *piso = new Particula();

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);
    particulas.emplace_back(particula3);
    particulas.emplace_back(particula4);
    particulas.emplace_back(particula5);
    particulas.emplace_back(piso);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_abajo(.0f, -1.0f), dir_arriba(.0f, 1.0f), dir_derecha(1.0f, .0f), dir_izquierda(-1.0f, .0f);
    sistema.agregar_interaccion(particula1, piso, dir_abajo);
    sistema.agregar_interaccion(particula2, piso, dir_abajo);
    sistema.agregar_interaccion(particula3, piso, dir_abajo);
    sistema.agregar_interaccion(particula4, piso, dir_abajo);
    sistema.agregar_interaccion(particula5, piso, dir_abajo);
    sistema.agregar_interaccion(piso, particula1, dir_arriba);
    sistema.agregar_interaccion(piso, particula2, dir_arriba);
    sistema.agregar_interaccion(piso, particula3, dir_arriba);
    sistema.agregar_interaccion(piso, particula4, dir_arriba);
    sistema.agregar_interaccion(piso, particula5, dir_arriba);
    sistema.agregar_interaccion(particula1, particula2, dir_derecha);
    sistema.agregar_interaccion(particula2, particula1, dir_izquierda);
    sistema.agregar_interaccion(particula2, particula3, dir_derecha);
    sistema.agregar_interaccion(particula3, particula2, dir_izquierda);
    sistema.agregar_interaccion(particula3, particula4, dir_derecha);
    sistema.agregar_interaccion(particula4, particula3, dir_izquierda);
    sistema.agregar_interaccion(particula4, particula5, dir_derecha);
    sistema.agregar_interaccion(particula5, particula4, dir_izquierda);

    sistema.expandir_fuerzas();

    ASSERT_EQ(particula1->m_velocidad, Vector2(.0f, .0f));
    ASSERT_EQ(particula2->m_velocidad, Vector2(.0f, .0f));
    ASSERT_EQ(particula3->m_velocidad, Vector2(.0f, .0f));
    ASSERT_EQ(particula4->m_velocidad, Vector2(.0f, .0f));
    ASSERT_EQ(particula5->m_velocidad, Vector2(10.0f, .0f));

    for (Particula *p : particulas)
        delete p;
}

class Particula_pos : public Particula
{
private:
    Vector2 m_posicion;

public:
    Particula_pos(float masa, Vector2 posicion, Vector2 velocidad, Vector2 fuerza, float coeficiente)
        : m_posicion(posicion), Particula(masa, velocidad, fuerza, coeficiente)
    {
    }

    Vector2 posicion_relativa(Particula_pos *particula)
    {
        return (particula->m_posicion - m_posicion);
    }
};

TEST(SistemaTest, Tres_particulas_con_las_fuerzas_de_peso_posicionadas_en_forma_de_piramide_las_de_abajo_se_mueven_para_los_costados)
{
    std::vector<Particula *> particulas;
    Particula_pos *particula1 = new Particula_pos(1.0f, Vector2(-0.2f, .0f), Vector2(.0f, .0f), Vector2(.0f, -10.0f), 1.0f);
    Particula_pos *particula2 = new Particula_pos(1.0f, Vector2(.0f, 1.0f), Vector2(.0f, .0f), Vector2(.0f, -10.0f), 1.0f);
    Particula_pos *particula3 = new Particula_pos(1.0f, Vector2(.2f, .0f), Vector2(.0f, .0f), Vector2(.0f, -10.0f), 1.0f);
    Particula *piso = new Particula();

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);
    particulas.emplace_back(particula3);
    particulas.emplace_back(piso);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_1_2 = particula1->posicion_relativa(particula2), dir_2_1 = particula2->posicion_relativa(particula1);
    Vector2 dir_1_3 = particula1->posicion_relativa(particula3), dir_3_1 = particula3->posicion_relativa(particula1);
    Vector2 dir_2_3 = particula2->posicion_relativa(particula3), dir_3_2 = particula3->posicion_relativa(particula2);
    sistema.agregar_interaccion(particula2, particula1, dir_2_1);
    sistema.agregar_interaccion(particula1, particula2, dir_1_2);
    sistema.agregar_interaccion(particula2, particula3, dir_2_3);
    sistema.agregar_interaccion(particula3, particula2, dir_3_2);
    sistema.agregar_interaccion(particula1, particula3, dir_1_3);
    sistema.agregar_interaccion(particula3, particula1, dir_3_1);

    Vector2 dir_abajo(.0f, -1.0f), dir_arriba(.0f, 1.0f);
    sistema.agregar_interaccion(particula1, piso, dir_abajo);
    sistema.agregar_interaccion(particula3, piso, dir_abajo);
    sistema.agregar_interaccion(piso, particula1, dir_arriba);
    sistema.agregar_interaccion(piso, particula3, dir_arriba);

    sistema.expandir_fuerzas();

    ASSERT_NEAR(particula1->m_velocidad.y, .0f, .01f);
    ASSERT_NEAR(particula2->m_velocidad.x, .0f, .01f);
    ASSERT_NEAR(particula3->m_velocidad.y, .0f, .01f);
    ASSERT_NEAR(particula1->m_velocidad.x, -1.0f * particula3->m_velocidad.x, .01f);

    for (Particula *p : particulas)
        delete p;
}

TEST(SistemaTest, Tres_particulas_sin_fuerzas_posicionadas_en_una_piramide_donde_la_de_mas_arriba_tiene_velocidad_se_mueven)
{
    std::vector<Particula *> particulas;
    Particula_pos *particula1 = new Particula_pos(1.0f, Vector2(-0.2f, .0f), Vector2(.0f, .0f), Vector2(.0f, .0f), 1.0f);
    Particula_pos *particula2 = new Particula_pos(1.0f, Vector2(.0f, 1.0f), Vector2(.0f, -10.0f), Vector2(.0f, .0f), 1.0f);
    Particula_pos *particula3 = new Particula_pos(1.0f, Vector2(.2f, .0f), Vector2(.0f, .0f), Vector2(.0f, .0f), 1.0f);

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);
    particulas.emplace_back(particula3);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_1_2 = particula1->posicion_relativa(particula2), dir_2_1 = particula2->posicion_relativa(particula1);
    Vector2 dir_1_3 = particula1->posicion_relativa(particula3), dir_3_1 = particula3->posicion_relativa(particula1);
    Vector2 dir_2_3 = particula2->posicion_relativa(particula3), dir_3_2 = particula3->posicion_relativa(particula2);
    sistema.agregar_interaccion(particula2, particula1, dir_2_1);
    sistema.agregar_interaccion(particula1, particula2, dir_1_2);
    sistema.agregar_interaccion(particula2, particula3, dir_2_3);
    sistema.agregar_interaccion(particula3, particula2, dir_3_2);
    sistema.agregar_interaccion(particula1, particula3, dir_1_3);
    sistema.agregar_interaccion(particula3, particula1, dir_3_1);

    sistema.expandir_fuerzas();

    EXPECT_NEAR(particula2->m_velocidad.x, .0f, .01f);
    EXPECT_NEAR(particula1->m_velocidad.x, -1.0f * particula3->m_velocidad.x, .01f);
    EXPECT_NEAR(particula1->m_velocidad.y, particula3->m_velocidad.y, .01f);

    for (Particula *p : particulas)
        delete p;
}

TEST(SistemaTest, Tres_particulas_sin_fuerzas_posicionadas_en_una_piramide_donde_la_de_mas_arriba_tiene_velocidad_se_mueven_hace_chochar_contra_el_piso)
{
    std::vector<Particula *> particulas;
    Particula_pos *particula1 = new Particula_pos(1.0f, Vector2(-0.2f, .0f), Vector2(.0f, .0f), Vector2(.0f, .0f), 1.0f);
    Particula_pos *particula2 = new Particula_pos(1.0f, Vector2(.0f, .22f), Vector2(.0f, -10.0f), Vector2(.0f, .0f), 1.0f);
    Particula_pos *particula3 = new Particula_pos(1.0f, Vector2(.2f, .0f), Vector2(.0f, .0f), Vector2(.0f, .0f), 1.0f);
    Particula *piso = new Particula();

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);
    particulas.emplace_back(particula3);
    particulas.emplace_back(piso);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_1_2 = particula1->posicion_relativa(particula2), dir_2_1 = particula2->posicion_relativa(particula1);
    Vector2 dir_1_3 = particula1->posicion_relativa(particula3), dir_3_1 = particula3->posicion_relativa(particula1);
    Vector2 dir_2_3 = particula2->posicion_relativa(particula3), dir_3_2 = particula3->posicion_relativa(particula2);
    sistema.agregar_interaccion(particula2, particula1, dir_2_1);
    sistema.agregar_interaccion(particula1, particula2, dir_1_2);
    sistema.agregar_interaccion(particula2, particula3, dir_2_3);
    sistema.agregar_interaccion(particula3, particula2, dir_3_2);
    sistema.agregar_interaccion(particula1, particula3, dir_1_3);
    sistema.agregar_interaccion(particula3, particula1, dir_3_1);

    Vector2 dir_abajo(.0f, -1.0f), dir_arriba(.0f, 1.0f);
    sistema.agregar_interaccion(particula1, piso, dir_abajo);
    sistema.agregar_interaccion(particula3, piso, dir_abajo);
    sistema.agregar_interaccion(piso, particula1, dir_arriba);
    sistema.agregar_interaccion(piso, particula3, dir_arriba);

    sistema.expandir_fuerzas();

    EXPECT_NEAR(particula2->m_velocidad.x, .0f, .01f);
    EXPECT_NEAR(particula1->m_velocidad.x, -1.0f * particula3->m_velocidad.x, .01f);
    EXPECT_NEAR(particula1->m_velocidad.y, particula3->m_velocidad.y, .01f);

    for (Particula *p : particulas)
        delete p;
}

TEST(SistemaTest, Dos_particulas_tiene_un_choque_inelastico_de_50_porciento)
{
    std::vector<Particula *> particulas;
    Particula_pos *particula1 = new Particula_pos(1.0f, Vector2(-1.0f, .0f), Vector2(1.0f, .0f), Vector2(.0f, .0f), .5f);
    Particula_pos *particula2 = new Particula_pos(1.0f, Vector2(1.0f, .0f), Vector2(-1.0f, .0f), Vector2(.0f, .0f), .5f);

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_1_2 = particula1->posicion_relativa(particula2), dir_2_1 = particula2->posicion_relativa(particula1);
    sistema.agregar_interaccion(particula2, particula1, dir_2_1);
    sistema.agregar_interaccion(particula1, particula2, dir_1_2);

    sistema.expandir_fuerzas();

    ASSERT_NEAR(particula1->m_velocidad.x, -.5f, .01f);
    ASSERT_NEAR(particula2->m_velocidad.x, .5f, .01f);

    for (Particula *p : particulas)
        delete p;
}

TEST(SistemaTest, Dos_particulas_tiene_un_choque_inelastico_de_25_porciento)
{
    std::vector<Particula *> particulas;
    Particula_pos *particula1 = new Particula_pos(1.0f, Vector2(-1.0f, .0f), Vector2(1.0f, .0f), Vector2(.0f, .0f), .25f);
    Particula_pos *particula2 = new Particula_pos(1.0f, Vector2(1.0f, .0f), Vector2(-1.0f, .0f), Vector2(.0f, .0f), .25f);

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_1_2 = particula1->posicion_relativa(particula2), dir_2_1 = particula2->posicion_relativa(particula1);
    sistema.agregar_interaccion(particula2, particula1, dir_2_1);
    sistema.agregar_interaccion(particula1, particula2, dir_1_2);

    sistema.expandir_fuerzas();

    ASSERT_NEAR(particula1->m_velocidad.x, -.25f, .01f);
    ASSERT_NEAR(particula2->m_velocidad.x, .25f, .01f);

    for (Particula *p : particulas)
        delete p;
}

TEST(SistemaTest, Dos_particulas_con_masas_diferentes_tiene_un_choque_inelastico_de_50_porciento)
{
    std::vector<Particula *> particulas;
    Particula_pos *particula1 = new Particula_pos(1.0f, Vector2(-1.0f, .0f), Vector2(1.0f, .0f), Vector2(.0f, .0f), .5f);
    Particula_pos *particula2 = new Particula_pos(2.0f, Vector2(1.0f, .0f), Vector2(-1.0f, .0f), Vector2(.0f, .0f), .5f);

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_1_2 = particula1->posicion_relativa(particula2), dir_2_1 = particula2->posicion_relativa(particula1);
    sistema.agregar_interaccion(particula2, particula1, dir_2_1);
    sistema.agregar_interaccion(particula1, particula2, dir_1_2);

    sistema.expandir_fuerzas();

    ASSERT_NEAR(particula1->m_velocidad.x, -1.0f, .01f);
    ASSERT_NEAR(particula2->m_velocidad.x, .0f, .01f);

    for (Particula *p : particulas)
        delete p;
}

TEST(SistemaTest, Dos_particulas_con_masas_diferentes_tiene_un_choque_inelastico_de_25_porciento)
{
    std::vector<Particula *> particulas;
    Particula_pos *particula1 = new Particula_pos(1.0f, Vector2(-1.0f, .0f), Vector2(1.0f, .0f), Vector2(.0f, .0f), .3f);
    Particula_pos *particula2 = new Particula_pos(2.0f, Vector2(1.0f, .0f), Vector2(-1.0f, .0f), Vector2(.0f, .0f), .3f);

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_1_2 = particula1->posicion_relativa(particula2), dir_2_1 = particula2->posicion_relativa(particula1);
    sistema.agregar_interaccion(particula2, particula1, dir_2_1);
    sistema.agregar_interaccion(particula1, particula2, dir_1_2);

    sistema.expandir_fuerzas();

    ASSERT_NEAR(particula1->m_velocidad.x, -.73333f, .01f);
    ASSERT_NEAR(particula2->m_velocidad.x, -.13333f, .01f);

    for (Particula *p : particulas)
        delete p;
}

TEST(SistemaTest, Dos_particulas_con_masas_diferentes_tiene_un_choque_plastico)
{
    std::vector<Particula *> particulas;
    Particula_pos *particula1 = new Particula_pos(1.0f, Vector2(-1.0f, .0f), Vector2(1.0f, .0f), Vector2(.0f, .0f), .0f);
    Particula_pos *particula2 = new Particula_pos(2.0f, Vector2(1.0f, .0f), Vector2(-1.0f, .0f), Vector2(.0f, .0f), .0f);

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_1_2 = particula1->posicion_relativa(particula2), dir_2_1 = particula2->posicion_relativa(particula1);
    sistema.agregar_interaccion(particula2, particula1, dir_2_1);
    sistema.agregar_interaccion(particula1, particula2, dir_1_2);

    sistema.expandir_fuerzas();

    ASSERT_NEAR(particula1->m_velocidad.x, -.33333f, .01f);
    ASSERT_NEAR(particula2->m_velocidad.x, -.33333f, .01f);

    for (Particula *p : particulas)
        delete p;
}

TEST(SistemaTest, Dos_particulas_de_la_misma_masa_tiene_un_choque_plastico)
{
    std::vector<Particula *> particulas;
    Particula_pos *particula1 = new Particula_pos(1.0f, Vector2(-1.0f, .0f), Vector2(1.0f, .0f), Vector2(.0f, .0f), .0f);
    Particula_pos *particula2 = new Particula_pos(1.0f, Vector2(1.0f, .0f), Vector2(-1.0f, .0f), Vector2(.0f, .0f), .0f);

    particulas.emplace_back(particula1);
    particulas.emplace_back(particula2);

    float dt = 1.0f;
    Sistema sistema(particulas, dt);

    Vector2 dir_1_2 = particula1->posicion_relativa(particula2), dir_2_1 = particula2->posicion_relativa(particula1);
    sistema.agregar_interaccion(particula2, particula1, dir_2_1);
    sistema.agregar_interaccion(particula1, particula2, dir_1_2);

    sistema.expandir_fuerzas();

    ASSERT_NEAR(particula1->m_velocidad.x, .0f, .01f);
    ASSERT_NEAR(particula2->m_velocidad.x, .0f, .01f);

    for (Particula *p : particulas)
        delete p;
}
