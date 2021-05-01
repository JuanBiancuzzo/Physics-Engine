#include "physics.h"

Fisicas::Fisicas(const Rectangulo &mundo)
    : c_qt(mundo)
{
}

Fisicas::~Fisicas()
{
    for (Body *body : c_bodys)
        delete body;
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
    // for (Particula *particula : c_particulas)
    // {
    // calcular fuerzas
    /*
             * rozamiento
             * interacciones con otros objetos
             * futuras otras fuerzas
             */
    // particula->aplicar_fuerza();
    // hacer un cache si la velocidad se hace muy grande
    // }

    for (Body *body : c_bodys)
    {
        body->actualizar(dt);
        c_qt.actualizar(body);
    }
}