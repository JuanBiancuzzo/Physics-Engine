#include "gtest/gtest.h"
#include "../src/sistema/sistema.h"

#include <math.h>

using namespace sistema;

class Particula_pos : public Particula
{
public:
    void actualizar(float dt)
    {
        // m_velocidad += (m_fuerza * dt) / m_cuerpo->m_masa;
        // m_fuerza *= .0f;
        // if (m_cuerpo->m_inercia != .0f)
        //     m_velocidad_angular += (m_torque * dt) / m_cuerpo->m_inercia;
        // m_torque *= .0f;
    }
};

void velocidades(std::vector<Particula *> particulas)
{
    std::cout << "Velocidades" << std::endl;
    for (Particula *particula : particulas)
        std::cout << " -> " << particula->velocidad();
}

TEST(SistemaTest, Dos_particulas_y_el_piso_sin_velocidad_ninguna_sus_fuerzas_finales_son_cero)
{
    cr::Circulo cuerpo1(Vector2(.0f, 3.0f), .0f, 1.0f);
    cr::InfoCuerpo info1(&cuerpo1, 1.0f);
    ParticulaDinamica particula1 = ParticulaDinamica(&info1, Vector2(), .0f, 1.0f);
    std::shared_ptr<Fuerza> fuerza1(new FuerzaAplicada(Vector2(.0f, -10.0f)));
    particula1.aplicar_fuerza(fuerza1);

    cr::Circulo cuerpo2(Vector2(.0f, 1.0f), .0f, 1.0f);
    cr::InfoCuerpo info2(&cuerpo2, 2.0f);
    ParticulaDinamica particula2 = ParticulaDinamica(&info2, Vector2(), .0f, 1.0f);
    std::shared_ptr<Fuerza> fuerza2(new FuerzaAplicada(Vector2(.0f, -20.0f)));
    particula2.aplicar_fuerza(fuerza2);

    cr::Poligono<2> cuerpo_linea({Vector2(1.0f, .0f), Vector2(-1.0f, .0f)});
    ParticulaEstatica piso = ParticulaEstatica(&cuerpo_linea);

    std::vector<Particula *> particulas = {&particula1, &particula2, &piso};
    Sistema sistema(particulas);

    sistema.agregar_interaccion(&particula1, &particula2);
    sistema.agregar_interaccion(&particula2, &piso);
    sistema.agregar_interaccion(&piso, &particula2);
    sistema.agregar_interaccion(&particula2, &particula1);

    sistema.expandir_interacciones();
    for (Particula *p : particulas)
        ((Particula_pos *)p)->actualizar(1.0f);

    ASSERT_EQ(particula1.velocidad(), Vector2());
    ASSERT_EQ(particula2.velocidad(), Vector2());
}

TEST(SistemaTest, Dos_particulas_y_el_piso_el_primero_con_velocidad_y_rebota_con_su_velocidad_invertida)
{
    cr::Circulo cuerpo1(Vector2(.0f, 3.0f), .0f, 1.0f);
    cr::InfoCuerpo info1(&cuerpo1, 1.0f);
    ParticulaDinamica particula1 = ParticulaDinamica(&info1, Vector2(.0f, -10.0f), .0f, 1.0f);
    std::shared_ptr<Fuerza> fuerza1(new FuerzaAplicada(Vector2(.0f, -10.0f)));
    particula1.aplicar_fuerza(fuerza1);

    cr::Circulo cuerpo2(Vector2(.0f, 1.0f), .0f, 1.0f);
    cr::InfoCuerpo info2(&cuerpo2, 2.0f);
    ParticulaDinamica particula2 = ParticulaDinamica(&info2, Vector2(), .0f, 1.0f);
    std::shared_ptr<Fuerza> fuerza2(new FuerzaAplicada(Vector2(.0f, -20.0f)));
    particula2.aplicar_fuerza(fuerza2);

    cr::Poligono<2> cuerpo_linea({Vector2(1.0f, .0f), Vector2(-1.0f, .0f)});
    ParticulaEstatica piso = ParticulaEstatica(&cuerpo_linea);

    std::vector<Particula *> particulas = {&particula1, &particula2, &piso};
    Sistema sistema(particulas);

    sistema.agregar_interaccion(&particula1, &particula2);
    sistema.agregar_interaccion(&particula2, &piso);
    sistema.agregar_interaccion(&piso, &particula2);
    sistema.agregar_interaccion(&particula2, &particula1);

    sistema.expandir_interacciones();
    for (Particula *p : particulas)
        ((Particula_pos *)p)->actualizar(1.0f);

    ASSERT_EQ(particula1.velocidad(), Vector2(.0f, 7.777f));
    ASSERT_EQ(particula2.velocidad(), Vector2(.0f, 4.444f));
}

// TEST(SistemaTest, Dos_particulas_sobre_el_piso_una_tiene_velocidad_y_terminan_intercambiando_velocidades)
// {
//     cr::Circulo cuerpo1(Vector2(-1.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(10.0f, .0f), .0f, 1.0f);
//     Fuerza fuerza1(Vector2(.0f, -10.0f));
//     particula1.aplicar_fuerza(&fuerza1);

//     cr::Circulo cuerpo2(Vector2(1.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 1.0f);
//     Particula particula2 = Particula(&info2, Vector2(), .0f, 1.0f);
//     Fuerza fuerza2(Vector2(.0f, -10.0f));
//     particula2.aplicar_fuerza(&fuerza2);

//     cr::Poligono<2> cuerpo_linea({Vector2(10.0f, .0f), Vector2(-10.0f, .0f)});
//     cr::InfoCuerpo info_linea(&cuerpo_linea, .0f);
//     Particula piso = Particula(&info_linea);

//     Sistema sistema({&particula1, &particula2, &piso});

//     sistema.agregar_interaccion(&particula1, &particula2);
//     sistema.agregar_interaccion(&particula2, &particula1);
//     sistema.agregar_interaccion(&particula1, &piso);
//     sistema.agregar_interaccion(&piso, &particula1);
//     sistema.agregar_interaccion(&particula2, &piso);
//     sistema.agregar_interaccion(&piso, &particula2);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2, &piso})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_EQ(particula1.m_velocidad, Vector2());
//     ASSERT_EQ(particula2.m_velocidad, Vector2(10.0f, .0f));
// }

// TEST(SistemaTest, Dos_particulas_sobre_el_piso_una_tienen_velocidades_y_hay_un_choque_elastico)
// {
//     cr::Circulo cuerpo1(Vector2(-1.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(30.0f, .0f), .0f, 1.0f);
//     Fuerza fuerza1(Vector2(.0f, -10.0f));
//     particula1.aplicar_fuerza(&fuerza1);

//     cr::Circulo cuerpo2(Vector2(1.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 2.0f);
//     Particula particula2 = Particula(&info2, Vector2(-30.0f, .0f), .0f, 1.0f);
//     Fuerza fuerza2(Vector2(.0f, -20.0f));
//     particula2.aplicar_fuerza(&fuerza2);

//     cr::Poligono<2> cuerpo_linea({Vector2(10.0f, .0f), Vector2(-10.0f, .0f)});
//     cr::InfoCuerpo info_linea(&cuerpo_linea, .0f);
//     Particula piso = Particula(&info_linea);

//     Sistema sistema({&particula1, &particula2, &piso});

//     sistema.agregar_interaccion(&particula1, &particula2);
//     sistema.agregar_interaccion(&particula2, &particula1);
//     sistema.agregar_interaccion(&particula1, &piso);
//     sistema.agregar_interaccion(&piso, &particula1);
//     sistema.agregar_interaccion(&particula2, &piso);
//     sistema.agregar_interaccion(&piso, &particula2);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2, &piso})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_EQ(particula1.m_velocidad, Vector2(-50.0f, .0f));
//     ASSERT_EQ(particula2.m_velocidad, Vector2(10.0f, .0f));
// }

// TEST(SistemaTest, Particula_estando_en_una_esquina_y_una_velocidad_horizontal_rebota_contra_la_pared)
// {
//     cr::Circulo cuerpo(Vector2(-1.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info(&cuerpo, 1.0f);
//     Particula particula = Particula(&info, Vector2(10.0f, .0f), .0f, 1.0f);
//     Fuerza fuerza(Vector2(.0f, -10.0f));
//     particula.aplicar_fuerza(&fuerza);

//     cr::Poligono<2> cuerpo_piso({Vector2(10.0f, .0f), Vector2(-10.0f, .0f)});
//     cr::InfoCuerpo info_piso(&cuerpo_piso, .0f);
//     Particula piso = Particula(&info_piso);

//     cr::Poligono<2> cuerpo_pared({Vector2(.0f, 10.0f), Vector2(.0f, -10.0f)});
//     cr::InfoCuerpo info_pared(&cuerpo_pared, .0f);
//     Particula pared = Particula(&info_pared);

//     Sistema sistema({&particula, &piso, &pared});

//     sistema.agregar_interaccion(&particula, &piso);
//     sistema.agregar_interaccion(&particula, &pared);
//     sistema.agregar_interaccion(&pared, &particula);
//     sistema.agregar_interaccion(&pared, &piso);
//     sistema.agregar_interaccion(&piso, &particula);
//     sistema.agregar_interaccion(&piso, &pared);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula, &piso, &pared})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_EQ(particula.m_velocidad, Vector2(-10.0f, .0f));
// }

// TEST(SistemaTest, Particula_choca_contra_el_piso_con_una_velocidad_y_rebota_terminando_con_la_velocidad_opuesta)
// {
//     cr::Circulo cuerpo(Vector2(.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info(&cuerpo, 1.0f);
//     Particula particula = Particula(&info, Vector2(.0f, -10.0f), .0f, 1.0f);
//     Fuerza fuerza(Vector2(.0f, -10.0f));
//     particula.aplicar_fuerza(&fuerza);

//     cr::Poligono<2> cuerpo_piso({Vector2(10.0f, .0f), Vector2(-10.0f, .0f)});
//     cr::InfoCuerpo info_piso(&cuerpo, .0f);
//     Particula piso = Particula(&info_piso);

//     Sistema sistema({&particula, &piso});

//     sistema.agregar_interaccion(&particula, &piso);
//     sistema.agregar_interaccion(&piso, &particula);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula, &piso})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_EQ(particula.m_velocidad, Vector2(.0f, 10.0f));
// }

// TEST(SistemaTest, Dos_particulas_con_velocidades_en_la_misma_direccion_la_que_esta_adelante_tiene_menor_velocidad)
// {
//     cr::Circulo cuerpo1(Vector2(.0f, 3.0f), .0f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(.0f, 10.0f / 3.0f), .0f, 1.0f);

//     cr::Circulo cuerpo2(Vector2(.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 2.0f);
//     Particula particula2 = Particula(&info2, Vector2(.0f, 20.0f / 3.0f), .0f, 1.0f);

//     Sistema sistema({&particula1, &particula2});

//     sistema.agregar_interaccion(&particula2, &particula1);
//     sistema.agregar_interaccion(&particula1, &particula2);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_EQ(particula1.m_velocidad, Vector2(.0f, 7.77f));
//     ASSERT_EQ(particula2.m_velocidad, Vector2(.0f, 4.44f));
// }

// TEST(SistemaTest, Simular_el_pendulo_de_newton_con_todas_las_particulas_de_la_misma_masa)
// {
//     cr::Circulo cuerpo1(Vector2(-4.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(10.0f, .0f), .0f, 1.0f);
//     Fuerza fuerza1(Vector2(.0f, -10.0f));
//     particula1.aplicar_fuerza(&fuerza1);

//     cr::Circulo cuerpo2(Vector2(-2.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 1.0f);
//     Particula particula2 = Particula(&info2, Vector2(.0f, .0f), .0f, 1.0f);
//     Fuerza fuerza2(Vector2(.0f, -10.0f));
//     particula2.aplicar_fuerza(&fuerza2);

//     cr::Circulo cuerpo3(Vector2(.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info3(&cuerpo3, 1.0f);
//     Particula particula3 = Particula(&info3, Vector2(.0f, .0f), .0f, 1.0f);
//     Fuerza fuerza3(Vector2(.0f, -10.0f));
//     particula3.aplicar_fuerza(&fuerza3);

//     cr::Circulo cuerpo4(Vector2(2.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info4(&cuerpo4, 1.0f);
//     Particula particula4 = Particula(&info4, Vector2(.0f, .0f), .0f, 1.0f);
//     Fuerza fuerza4(Vector2(.0f, -10.0f));
//     particula4.aplicar_fuerza(&fuerza4);

//     cr::Circulo cuerpo5(Vector2(4.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info5(&cuerpo5, 1.0f);
//     Particula particula5 = Particula(&info5, Vector2(.0f, .0f), .0f, 1.0f);
//     Fuerza fuerza5(Vector2(.0f, -10.0f));
//     particula5.aplicar_fuerza(&fuerza5);

//     cr::Poligono<2> cuerpo_piso({Vector2(10.0f, .0f), Vector2(-10.0f, .0f)});
//     cr::InfoCuerpo info_piso(&cuerpo_piso, .0f);
//     Particula piso = Particula(&info_piso);

//     Sistema sistema({&particula1, &particula2, &particula3, &particula4, &particula5, &piso});

//     sistema.agregar_interaccion(&particula1, &piso);
//     sistema.agregar_interaccion(&particula2, &piso);
//     sistema.agregar_interaccion(&particula3, &piso);
//     sistema.agregar_interaccion(&particula4, &piso);
//     sistema.agregar_interaccion(&particula5, &piso);
//     sistema.agregar_interaccion(&piso, &particula1);
//     sistema.agregar_interaccion(&piso, &particula2);
//     sistema.agregar_interaccion(&piso, &particula3);
//     sistema.agregar_interaccion(&piso, &particula4);
//     sistema.agregar_interaccion(&piso, &particula5);
//     sistema.agregar_interaccion(&particula1, &particula2);
//     sistema.agregar_interaccion(&particula2, &particula1);
//     sistema.agregar_interaccion(&particula2, &particula3);
//     sistema.agregar_interaccion(&particula3, &particula2);
//     sistema.agregar_interaccion(&particula3, &particula4);
//     sistema.agregar_interaccion(&particula4, &particula3);
//     sistema.agregar_interaccion(&particula4, &particula5);
//     sistema.agregar_interaccion(&particula5, &particula4);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2, &particula3, &particula4, &particula5, &piso})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_EQ(particula1.m_velocidad, Vector2(.0f, .0f));
//     ASSERT_EQ(particula2.m_velocidad, Vector2(.0f, .0f));
//     ASSERT_EQ(particula3.m_velocidad, Vector2(.0f, .0f));
//     ASSERT_EQ(particula4.m_velocidad, Vector2(.0f, .0f));
//     ASSERT_EQ(particula5.m_velocidad, Vector2(10.0f, .0f));
// }

// TEST(SistemaTest, Tres_particulas_con_las_fuerzas_de_peso_posicionadas_en_forma_de_piramide_las_de_abajo_se_mueven_para_los_costados)
// {
//     cr::Circulo cuerpo1(Vector2(-1.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(.0f, .0f), .0f, 1.0f);
//     Fuerza fuerza1(Vector2(.0f, -10.0f));
//     particula1.aplicar_fuerza(&fuerza1);

//     cr::Circulo cuerpo2(Vector2(.0f, .99f + sqrt(3)), .0f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 1.0f);
//     Particula particula2 = Particula(&info2, Vector2(.0f, .0f), .0f, 1.0f);
//     Fuerza fuerza2(Vector2(.0f, -10.0f));
//     particula2.aplicar_fuerza(&fuerza2);

//     cr::Circulo cuerpo3(Vector2(1.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info3(&cuerpo3, 1.0f);
//     Particula particula3 = Particula(&info3, Vector2(.0f, .0f), .0f, 1.0f);
//     Fuerza fuerza3(Vector2(.0f, -10.0f));
//     particula3.aplicar_fuerza(&fuerza3);

//     cr::Poligono<2> cuerpo_piso({Vector2(10.0f, .0f), Vector2(-10.0f, .0f)});
//     cr::InfoCuerpo info_piso(&cuerpo_piso, .0f);
//     Particula piso = Particula(&info_piso);

//     Sistema sistema({&particula1, &particula2, &particula3, &piso});

//     sistema.agregar_interaccion(&particula2, &particula1);
//     sistema.agregar_interaccion(&particula2, &particula3);
//     sistema.agregar_interaccion(&particula1, &particula2);
//     sistema.agregar_interaccion(&particula3, &particula2);
//     sistema.agregar_interaccion(&particula1, &particula3);
//     sistema.agregar_interaccion(&particula3, &particula1);
//     sistema.agregar_interaccion(&particula1, &piso);
//     sistema.agregar_interaccion(&piso, &particula1);
//     sistema.agregar_interaccion(&particula3, &piso);
//     sistema.agregar_interaccion(&piso, &particula3);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2, &particula3, &piso})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_NEAR(particula1.m_velocidad.y, .0f, .01f);
//     ASSERT_NEAR(particula2.m_velocidad.x, .0f, .01f);
//     ASSERT_NEAR(particula3.m_velocidad.y, .0f, .01f);
//     ASSERT_NEAR(particula1.m_velocidad.x, -1.0f * particula3.m_velocidad.x, .01f);
// }

// TEST(SistemaTest, Tres_particulas_sin_fuerzas_posicionadas_en_una_piramide_donde_la_de_mas_arriba_tiene_velocidad_se_mueven)
// {
//     cr::Circulo cuerpo1(Vector2(-1.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(.0f, .0f), .0f, 1.0f);

//     cr::Circulo cuerpo2(Vector2(.0f, .99f + sqrt(3)), .0f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 1.0f);
//     Particula particula2 = Particula(&info2, Vector2(.0f, -10.0f), .0f, 1.0f);

//     cr::Circulo cuerpo3(Vector2(1.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info3(&cuerpo3, 1.0f);
//     Particula particula3 = Particula(&info3, Vector2(.0f, .0f), .0f, 1.0f);

//     Sistema sistema({&particula1, &particula2, &particula3});

//     sistema.agregar_interaccion(&particula2, &particula1);
//     sistema.agregar_interaccion(&particula2, &particula3);
//     sistema.agregar_interaccion(&particula1, &particula2);
//     sistema.agregar_interaccion(&particula3, &particula2);
//     sistema.agregar_interaccion(&particula1, &particula3);
//     sistema.agregar_interaccion(&particula3, &particula1);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2, &particula3})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     EXPECT_NEAR(particula2.m_velocidad.x, .0f, .01f);
//     EXPECT_NEAR(particula1.m_velocidad.x, -1.0f * particula3.m_velocidad.x, .01f);
//     EXPECT_NEAR(particula1.m_velocidad.y, particula3.m_velocidad.y, .01f);
// }

// TEST(SistemaTest, Tres_particulas_sin_fuerzas_posicionadas_en_una_piramide_donde_la_de_mas_arriba_tiene_velocidad_se_mueven_hace_chochar_contra_el_piso)
// {
//     cr::Circulo cuerpo1(Vector2(-1.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(.0f, .0f), .0f, 1.0f);

//     cr::Circulo cuerpo2(Vector2(.0f, .99f + sqrt(3)), .0f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 1.0f);
//     Particula particula2 = Particula(&info2, Vector2(.0f, -10.0f), .0f, 1.0f);

//     cr::Circulo cuerpo3(Vector2(1.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info3(&cuerpo3, 1.0f);
//     Particula particula3 = Particula(&info3, Vector2(.0f, .0f), .0f, 1.0f);

//     cr::Poligono<2> cuerpo_piso({Vector2(10.0f, .0f), Vector2(-10.0f, .0f)});
//     cr::InfoCuerpo info_piso(&cuerpo_piso, .0f);
//     Particula piso = Particula(&info_piso);

//     Sistema sistema({&particula1, &particula2, &particula3, &piso});

//     sistema.agregar_interaccion(&particula2, &particula1);
//     sistema.agregar_interaccion(&particula2, &particula3);
//     sistema.agregar_interaccion(&particula1, &particula2);
//     sistema.agregar_interaccion(&particula3, &particula2);
//     sistema.agregar_interaccion(&particula1, &particula3);
//     sistema.agregar_interaccion(&particula3, &particula1);
//     sistema.agregar_interaccion(&particula1, &piso);
//     sistema.agregar_interaccion(&piso, &particula1);
//     sistema.agregar_interaccion(&particula3, &piso);
//     sistema.agregar_interaccion(&piso, &particula3);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2, &particula3, &piso})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     EXPECT_NEAR(particula2.m_velocidad.x, .0f, .01f);
//     EXPECT_NEAR(particula1.m_velocidad.x, -1.0f * particula3.m_velocidad.x, .01f);
//     EXPECT_NEAR(particula1.m_velocidad.y, particula3.m_velocidad.y, .01f);
// }

// TEST(SistemaTest, Dos_particulas_tiene_un_choque_inelastico_de_50_porciento)
// {
//     cr::Circulo cuerpo1(Vector2(-1.0f, .0f), .0f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(1.0f, .0f), .0f, .5f);

//     cr::Circulo cuerpo2(Vector2(1.0f, .0f), .0f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 1.0f);
//     Particula particula2 = Particula(&info2, Vector2(-1.0f, .0f), .0f, .5f);

//     Sistema sistema({&particula1, &particula2});

//     sistema.agregar_interaccion(&particula1, &particula2);
//     sistema.agregar_interaccion(&particula2, &particula1);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_NEAR(particula1.m_velocidad.x, -.5f, .01f);
//     ASSERT_NEAR(particula2.m_velocidad.x, .5f, .01f);
// }

// TEST(SistemaTest, Dos_particulas_tiene_un_choque_inelastico_de_25_porciento)
// {
//     cr::Circulo cuerpo1(Vector2(-1.0f, .0f), .0f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(1.0f, .0f), .0f, .25f);

//     cr::Circulo cuerpo2(Vector2(1.0f, .0f), .0f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 1.0f);
//     Particula particula2 = Particula(&info2, Vector2(-1.0f, .0f), .0f, .25f);

//     Sistema sistema({&particula1, &particula2});

//     sistema.agregar_interaccion(&particula1, &particula2);
//     sistema.agregar_interaccion(&particula2, &particula1);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_NEAR(particula1.m_velocidad.x, -.25f, .01f);
//     ASSERT_NEAR(particula2.m_velocidad.x, .25f, .01f);
// }

// TEST(SistemaTest, Dos_particulas_con_masas_diferentes_tiene_un_choque_inelastico_de_50_porciento)
// {
//     cr::Circulo cuerpo1(Vector2(-1.0f, .0f), .0f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(1.0f, .0f), .0f, .5f);

//     cr::Circulo cuerpo2(Vector2(1.0f, .0f), .0f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 2.0f);
//     Particula particula2 = Particula(&info2, Vector2(-1.0f, .0f), .0f, .5f);

//     Sistema sistema({&particula1, &particula2});

//     sistema.agregar_interaccion(&particula1, &particula2);
//     sistema.agregar_interaccion(&particula2, &particula1);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_NEAR(particula1.m_velocidad.x, -1.0f, .01f);
//     ASSERT_NEAR(particula2.m_velocidad.x, .0f, .01f);
// }

// TEST(SistemaTest, Dos_particulas_con_masas_diferentes_tiene_un_choque_inelastico_de_30_porciento)
// {
//     cr::Circulo cuerpo1(Vector2(-1.0f, .0f), .0f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(1.0f, .0f), .0f, .3f);

//     cr::Circulo cuerpo2(Vector2(1.0f, .0f), .0f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 2.0f);
//     Particula particula2 = Particula(&info2, Vector2(-1.0f, .0f), .0f, .3f);

//     Sistema sistema({&particula1, &particula2});

//     sistema.agregar_interaccion(&particula1, &particula2);
//     sistema.agregar_interaccion(&particula2, &particula1);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_NEAR(particula1.m_velocidad.x, -.73333f, .01f);
//     ASSERT_NEAR(particula2.m_velocidad.x, -.13333f, .01f);
// }

// TEST(SistemaTest, Dos_particulas_con_masas_diferentes_tiene_un_choque_plastico)
// {
//     cr::Circulo cuerpo1(Vector2(-1.0f, .0f), .0f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(1.0f, .0f), .0f, .0f);

//     cr::Circulo cuerpo2(Vector2(1.0f, .0f), .0f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 2.0f);
//     Particula particula2 = Particula(&info2, Vector2(-1.0f, .0f), .0f, .0f);

//     Sistema sistema({&particula1, &particula2});

//     sistema.agregar_interaccion(&particula1, &particula2);
//     sistema.agregar_interaccion(&particula2, &particula1);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_NEAR(particula1.m_velocidad.x, -.33333f, .01f);
//     ASSERT_NEAR(particula2.m_velocidad.x, -.33333f, .01f);
// }

// TEST(SistemaTest, Dos_particulas_de_la_misma_masa_tiene_un_choque_plastico)
// {
//     cr::Circulo cuerpo1(Vector2(-1.0f, .0f), .0f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(1.0f, .0f), .0f, .0f);

//     cr::Circulo cuerpo2(Vector2(1.0f, .0f), .0f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 1.0f);
//     Particula particula2 = Particula(&info2, Vector2(-1.0f, .0f), .0f, .0f);

//     Sistema sistema({&particula1, &particula2});

//     sistema.agregar_interaccion(&particula1, &particula2);
//     sistema.agregar_interaccion(&particula2, &particula1);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_NEAR(particula1.m_velocidad.x, .0, .01f);
//     ASSERT_NEAR(particula2.m_velocidad.x, .0f, .01f);
// }

// TEST(SistemaTest, Dos_particulas_de_la_misma_masa_tiene_un_choque_inelastico_de_50_porciento_en_dos_dimensiones)
// {
//     cr::Circulo cuerpo1(Vector2(.0f, sqrt(2)), .0f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(.0f, -1.0f), .0f, .5f);

//     cr::Circulo cuerpo2(Vector2(sqrt(2), .0f), .0f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 1.0f);
//     Particula particula2 = Particula(&info2, Vector2(-1.0f, .0f), .0f, .5f);

//     Sistema sistema({&particula1, &particula2});

//     sistema.agregar_interaccion(&particula1, &particula2);
//     sistema.agregar_interaccion(&particula2, &particula1);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_EQ(particula1.m_velocidad, Vector2(-.75f, -.25f));
//     ASSERT_EQ(particula2.m_velocidad, Vector2(-.25f, -.75f));
// }

// TEST(SistemaTest, Dos_particulas_de_la_misma_masa_tiene_un_choque_inelastico_de_5_porciento_en_dos_dimensiones)
// {
//     cr::Circulo cuerpo1(Vector2(.0f, sqrt(2)), .0f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(.0f, -1.0f), .0f, .05f);

//     cr::Circulo cuerpo2(Vector2(sqrt(2), .0f), .0f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 1.0f);
//     Particula particula2 = Particula(&info2, Vector2(-1.0f, .0f), .0f, .05f);

//     Sistema sistema({&particula1, &particula2});

//     sistema.agregar_interaccion(&particula1, &particula2);
//     sistema.agregar_interaccion(&particula2, &particula1);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_EQ(particula1.m_velocidad, Vector2(-.525f, -.475f));
//     ASSERT_EQ(particula2.m_velocidad, Vector2(-.475f, -.525f));
// }

// TEST(SistemaTest, Una_particula_choca_contra_la_esquina_y_el_choque_es_plastico_haciendo_que_su_velocidad_sea_cero)
// {
//     cr::Circulo cuerpo(Vector2(-1.0f, 1.0f), .0f, 1.0f);
//     cr::InfoCuerpo info(&cuerpo, 1.0f);
//     Particula particula = Particula(&info, Vector2(10.0f, -10.0f), .0f, .0f);
//     Fuerza fuerza(Vector2(.0f, -10.0f));
//     particula.aplicar_fuerza(&fuerza);

//     cr::Poligono<2> cuerpo_piso({Vector2(10.0f, .0f), Vector2(-10.0f, .0f)});
//     cr::InfoCuerpo info_piso(&cuerpo_piso, .0f);
//     Particula piso = Particula(&info_piso);

//     cr::Poligono<2> cuerpo_pared({Vector2(.0f, 10.0f), Vector2(.0f, -10.0f)});
//     cr::InfoCuerpo info_pared(&cuerpo_pared, 1.0f);
//     Particula pared = Particula(&info_pared);

//     Sistema sistema({&particula, &piso, &pared});

//     sistema.agregar_interaccion(&particula, &pared);
//     sistema.agregar_interaccion(&pared, &particula);
//     sistema.agregar_interaccion(&particula, &piso);
//     sistema.agregar_interaccion(&piso, &particula);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula, &piso, &pared})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_EQ(particula.m_velocidad, Vector2());
// }

// TEST(SistemaTest, Un_rectangulo_se_mantiene_sin_rotar_contra_una_esquina)
// {
//     cr::Rectangulo cuerpo(Vector2(-10.0f, 10.0f), .0f, 10.0f, 10.0f);
//     cr::InfoCuerpo info(&cuerpo, 1.0f);
//     Particula particula = Particula(&info, Vector2(), .0f, 1.0f);
//     Fuerza fuerza(Vector2(.0f, -10.0f));
//     particula.aplicar_fuerza(&fuerza);

//     cr::Poligono<2> cuerpo_piso({Vector2(10.0f, .0f), Vector2(.0f, .0f)});
//     cr::InfoCuerpo info_piso(&cuerpo_piso, .0f);
//     Particula piso = Particula(&info_piso);

//     cr::Poligono<2> cuerpo_pared({Vector2(.0f, 10.0f), Vector2(.0f, .0f)}); // si es .0f, 10.0f tira un error entonces revisar eso
//     cr::InfoCuerpo info_pared(&cuerpo_pared, .0f);
//     Particula pared = Particula(&info_pared);

//     Sistema sistema({&particula, &piso, &pared});

//     sistema.agregar_interaccion(&particula, &pared);
//     sistema.agregar_interaccion(&pared, &particula);
//     sistema.agregar_interaccion(&particula, &piso);
//     sistema.agregar_interaccion(&piso, &particula);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula, &piso, &pared})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     ASSERT_NEAR(particula.m_velocidad_angular, .0f, .01f);
// }

// TEST(SistemaTest, Dos_particulas_rectangulares_chocan_produciendo_una_rotacion)
// {
//     cr::Rectangulo cuerpo1(Vector2(1.5f, 1.0f), .0f, 1.5f, 1.0f);
//     cr::InfoCuerpo info1(&cuerpo1, 1.0f);
//     Particula particula1 = Particula(&info1, Vector2(.0f, -1.0f), .0f, 1.0f);

//     cr::Rectangulo cuerpo2(Vector2(-1.5f, -1.0f), .0f, 1.5f, 1.0f);
//     cr::InfoCuerpo info2(&cuerpo2, 1.0f);
//     Particula particula2 = Particula(&info2, Vector2(), .0f, 1.0f);

//     Sistema sistema({&particula1, &particula2});

//     sistema.agregar_interaccion(&particula1, &particula2);
//     sistema.agregar_interaccion(&particula2, &particula1);

//     sistema.expandir_interacciones();
//     for (Particula *p : {&particula1, &particula2})
//         ((Particula_pos *)p)->actualizar(1.0f);

//     std::cout << particula1.m_velocidad_angular << std::endl;
//     std::cout << particula2.m_velocidad_angular << std::endl;

//     ASSERT_TRUE(particula1.m_velocidad_angular < .0f);
//     ASSERT_TRUE(particula2.m_velocidad_angular < .0f);
// }