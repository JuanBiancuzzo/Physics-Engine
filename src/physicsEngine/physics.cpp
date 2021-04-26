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

void Fisicas::insertar_particula(const Particula &particula)
{
    Particula *p = new Particula(particula.c_pos, particula.c_masa, particula.c_radio);
    c_qt.insertar(p);
    c_particulas.emplace_back(p);
}

void Fisicas::insertar_particula(const Vector2 &pos)
{
    insertar_particula(Particula(pos));
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