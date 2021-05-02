#include "physics.h"

Fisicas::Fisicas(const Rectangulo &mundo)
    : c_qt(mundo), gravedad(.0f, -9.8f)
{
}

Fisicas::~Fisicas()
{
    c_particulas.clear();
}

bool Fisicas::lugar_libre(const Particula *particula)
{
    return !c_qt.cantidad(particula->c_estructura);
}

bool Fisicas::insertar_particula(Particula *particula)
{
    if (!lugar_libre(particula))
        return false;

    c_qt.insertar(particula);
    c_particulas.emplace_back(particula);
    return true;
}

void Fisicas::mostrar() const
{
    // cuando tenga una forma de renderizas aca deberia estar
}

void Fisicas::avanzar(const float dt)
{

    for (Particula *particula : c_particulas)
    {
        particula->c_fuerza += gravedad;
        // calcular fuerzas
        /*
             * rozamiento
             * interacciones con otros objetos
             * futuras otras fuerzas
             */
        // particula->aplicar_fuerza();
        // hacer un cache si la velocidad se hace muy grande
    }

    resolverColisiones(dt);

    for (Particula *particula : c_particulas)
    {
        particula->actualizar(dt);
        c_qt.actualizar(particula);
    }
}

void Fisicas::resolverColisiones(const float dt)
{
    /* 
     * seria mejor tener un array de grafos asi se puede paralelizar
     * pero como todavia no se como hacer eso, voy a poderlo en un
     * solo grafo todo y deberia ser capaz
     */

    Vector2 fuerza = particula->c_fuerza + (particula->c_vel * particula->c_masa) / dt;

    // Grafo grafo_colision;
    // for (Particula *particula : c_particulas)
    // {
    //     std::vector<Entidad *> colisiones;
    //     c_qt.buscar(particula->c_estructura, colisiones);

    //     for (Entidad *colision : colisiones)
    //         grafo_colision.agregar_vinculo(particula, colision);
    // }
    // grafo_colision.expandir_fuerzas();
}
