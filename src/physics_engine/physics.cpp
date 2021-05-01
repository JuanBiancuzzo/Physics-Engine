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
    if (!particula->c_estructura)
        return true;
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
    // c_particulas esta ordenado de mayor velocidad a menor velocidad - aka un heap
    for (Particula *particula : c_particulas)
    {
        particula->c_acc += gravedad / particula->c_masa;
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
    std::vector<Colision> colisiones;

    for (Particula *particula : c_particulas)
    {

        std::vector<Entidad *> choques;
        c_qt.buscar(particula->c_estructura, choques);
        for (Entidad *c : choques)
        {
            Particula *colision = (Particula *)c;
            if (particula == colision)
                return;
            colisiones.push_back(Colision(particula, colision));
        }
    }
}