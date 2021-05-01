#include "physics.h"

Fisicas::Fisicas(const Rectangulo &mundo)
    : c_qt(mundo), gravedad(.0f, -9.8f)
{
}

Fisicas::~Fisicas()
{
    c_bodys.clear();
}

bool Fisicas::lugar_libre(const Body *body)
{
    if (!body->c_estructura)
        return true;
    return !c_qt.cantidad(body->c_estructura);
}

bool Fisicas::insertar_particula(Body *body)
{
    if (!lugar_libre(body))
        return false;

    c_qt.insertar(body);
    c_bodys.emplace_back(body);
    return true;
}

void Fisicas::mostrar() const
{
    // cuando tenga una forma de renderizas aca deberia estar
}

void Fisicas::avanzar(const float dt)
{
    // c_particulas esta ordenado de mayor velocidad a menor velocidad - aka un heap
    for (Body *body : c_bodys)
    {
        body->c_acc += gravedad / body->c_masa;
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

    for (Body *body : c_bodys)
    {
        body->actualizar(dt);
        c_qt.actualizar(body);
    }
}

void Fisicas::resolverColisiones(const float dt)
{
    std::vector<Colision> colisiones;

    for (Body *body : c_bodys)
    {

        std::vector<Entidad *> choques;
        c_qt.buscar(body->c_estructura, choques);
        for (auto colision : choques)
        {
            if (body == colision)
                return;
            // colisiones.push_back({body, colision});
        }
    }
}