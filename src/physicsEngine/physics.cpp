#include "headers/physics.h"

Fisicas::Fisicas(const Rectangulo &mundo)
    : c_qt(mundo)
{
}

Fisicas::~Fisicas()
{
    for (Particula *particula : c_particulas)
        delete particula;
}

bool Fisicas::lugar_libre(const Particula &particula)
{
    float r = particula.c_radio;
    return !c_qt.cantidad(Rectangulo(particula.c_pos, r * 2, r * 2));
}

bool Fisicas::insertar_particula(const Particula &particula)
{
    if (!lugar_libre(particula))
        return false;

    Particula *p = new Particula(particula.c_pos, particula.c_masa, particula.c_radio);
    c_qt.insertar(p);
    c_particulas.emplace_back(p);
    return true;
}

bool Fisicas::insertar_particula(const Vector2 &pos)
{
    return insertar_particula(Particula(pos));
}

void Fisicas::mostrar() const
{
    // cuando tenga una forma de renderizas aca deberia estar
}

void Fisicas::avanzar(const float delta_tiempo)
{
    for (Particula *particula : c_particulas)
    {
        // calcular fuerzas
        /*
             * rozamiento
             * interacciones con otros objetos
             * futuras otras fuerzas
             */
        // particula->aplicar_fuerza();
    }

    for (Particula *particula : c_particulas)
    {
        particula->actualizar(delta_tiempo);
        c_qt.actualizar(*particula);
    }
}