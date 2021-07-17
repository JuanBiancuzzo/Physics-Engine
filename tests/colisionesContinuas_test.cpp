#include "gtest/gtest.h"
#include "../src/colisionesContinuas.h"

using namespace cc;

void velocidades(std::vector<Particula *> particulas)
{
    std::cout << "Velocidades" << std::endl;
    for (Particula *particula : particulas)
        std::cout << "Particula: x = " << particula->m_velocidad.x << ", y = " << particula->m_velocidad.y << std::endl;
}

TEST(ColisionesContinuas, Dos_particulas_circulares_chocan_entre_frame_deberian_cambiar_de_camino)
{
    cr::AABB area(Vector2(), 10.0f, 10.0f);
    cr::Circulo circulo1(Vector2(.0f, 5.0f), 1.0f);
    Particula particula1(1.0f, &circulo1, Vector2(.0f, -6.0f), 1.0f);
    cr::Circulo circulo2(Vector2(5.0f, .0f), 1.0f);
    Particula particula2(2.0f, &circulo2, Vector2(-10.0f, .0f), 1.0f);
    float dt = 1.0f;

    SistemaDeParticulas sp(area, {&particula1, &particula2}, dt);
    sp.avanzar_frame();

    velocidades({&particula1, &particula2});

    ASSERT_EQ(particula1.m_cuerpo->m_posicion, Vector2(.0f, 3.0f));
    ASSERT_EQ(particula1.m_velocidad, Vector2(.0f, 2.0f));
    ASSERT_EQ(particula2.m_cuerpo->m_posicion, Vector2(-5.0f, -2.0f));
    ASSERT_EQ(particula2.m_velocidad, Vector2(-10.0f, -4.0f));
}