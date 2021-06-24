#include "gtest/gtest.h"
#include "../src/sistema.h"

using namespace sistema;

class Body : public Particula
{
public:
    Vector2 m_pos;

public:
    Body(Vector2 posicion, Vector2 velocidad, Vector2 fuerza, float masa)
        : m_pos(posicion), Particula(masa, velocidad, fuerza)
    {
    }

    Body(Vector2 posicion, bool es_estatico)
        : m_pos(posicion), Particula(es_estatico)
    {
    }

    void actualizar(float dt)
    {
        m_velocidad += (m_fuerza * dt) / m_masa;
    }

    Vector2 direccion_normal(Body *body)
    {
        return (body->m_pos - m_pos).normal();
    }
};

// test donde hay un piso, y dos particulas una encima de la otra
TEST(SistemaTest, Dos_particulas_y_el_piso_sin_velocidad_ninguna_sus_fuerzas_finales_son_cero)
{
    float dt = 1.0f;
    Sistema sistema(1.0f);
    Body *particula1 = new Body(Vector2(.0f, 10.0f), Vector2(), Vector2(.0f, -10.0f), 1.0f);
    Body *particula2 = new Body(Vector2(.0f, 5.0f), Vector2(), Vector2(.0f, -20.0f), 2.0f);
    Body *piso = new Body(Vector2(), true);

    sistema.agregar_particula(particula1);
    sistema.agregar_particula(particula2);
    sistema.agregar_particula(piso);

    sistema.agregar_interaccion(particula1, particula2, particula1->direccion_normal(particula2));
    sistema.agregar_interaccion(particula2, piso, particula2->direccion_normal(piso));
    sistema.agregar_interaccion(piso, particula2, piso->direccion_normal(particula2));
    sistema.agregar_interaccion(particula2, particula1, particula2->direccion_normal(particula1));

    sistema.expandir_fuerzas();

    ASSERT_EQ(particula1->m_fuerza, Vector2());
    ASSERT_EQ(particula2->m_fuerza, Vector2());

    delete particula1;
    delete particula2;
    delete piso;
}

TEST(SistemaTest, Dos_particulas_y_el_piso_el_primero_con_velocidad_sus_fuerzas_finales_son_cero)
{
    float dt = 1.0f;
    Sistema sistema(dt);
    Body *particula1 = new Body(Vector2(.0f, 10.0f), Vector2(.0f, -10.0f), Vector2(.0f, -10.0f), 1.0f);
    Body *particula2 = new Body(Vector2(.0f, 5.0f), Vector2(), Vector2(.0f, -20.0f), 2.0f);
    Body *piso = new Body(Vector2(), true);

    sistema.agregar_particula(particula1);
    sistema.agregar_particula(particula2);
    sistema.agregar_particula(piso);

    sistema.agregar_interaccion(particula1, particula2, particula1->direccion_normal(particula2));
    sistema.agregar_interaccion(particula2, piso, particula2->direccion_normal(piso));
    sistema.agregar_interaccion(piso, particula2, piso->direccion_normal(particula2));
    sistema.agregar_interaccion(particula2, particula1, particula2->direccion_normal(particula1));

    std::cout << "Antes" << std::endl;
    std::cout << particula1->m_velocidad.x << ", " << particula1->m_velocidad.y << std::endl;

    sistema.expandir_fuerzas();
    particula1->actualizar(dt);

    std::cout << "Despues" << std::endl;
    std::cout << particula1->m_velocidad.x << ", " << particula1->m_velocidad.y << std::endl;

    ASSERT_EQ(particula1->m_velocidad, Vector2(.0f, 10.0f));
    ASSERT_EQ(particula2->m_fuerza, Vector2());

    delete particula1;
    delete particula2;
    delete piso;
}

// test donde hay dos particulas cayendose, a la misma velocidad por lo que no deberia haber un choque -> a determinar

// test donde hay dos particulas cayendose, la de abajo con una mayor velocidad por lo que no deberia haber un choque -> a determinar

// test donde hay dos particulas cayendose, la de arriba con mayor velocidad produciendose un choque

// test donde hay una bala y un cuerpo sin fuerza inicial volando, y terminan intercambiando velocidades
TEST(SistemaTest, Una_bala_con_velocidad_y_un_bloque_sin_velcodad_chocan_e_intercambian_velocidades)
{
    float dt = 1.0f;
    Sistema sistema(dt);
    Body *particula1 = new Body(Vector2(-5.0f, .0f), Vector2(10.0f, .0f), Vector2(.0f, -10.0f), 1.0f);
    Body *particula2 = new Body(Vector2(5.0f, .0f), Vector2(.0f, .0f), Vector2(.0f, -20.0f), 2.0f);

    sistema.agregar_particula(particula1);
    sistema.agregar_particula(particula2);

    sistema.agregar_interaccion(particula1, particula2, particula1->direccion_normal(particula2));
    sistema.agregar_interaccion(particula2, particula1, particula2->direccion_normal(particula1));

    sistema.expandir_fuerzas();
    
    particula1->actualizar(dt);
    particula2->actualizar(dt);

    ASSERT_EQ(particula1->m_velocidad, Vector2(0.0f, -10.0f));
    ASSERT_EQ(particula2->m_velocidad, Vector2(10.0f, -10.0f));

    delete particula1;
    delete particula2;
}