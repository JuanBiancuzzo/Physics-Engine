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
    //Vector2 fuerza = particula->c_fuerza + (particula->c_vel * particula->c_masa) / dt;

    Sistema_particulas sistema(c_particulas, c_qt);
    sistema.aplicar_fuerzas(dt);
}

Sistema_particulas::Sistema_particulas(std::vector<Particula *> &particulas, QuadTree &qt)
{
    for (Particula *particula : particulas)
        if (!hay_entidad(particula, c_particulas))
            crear_grafo(particula, qt);
}

bool Sistema_particulas::hay_entidad(Entidad *entidad, std::vector<Entidad *> entidades)
{
    for (Entidad *e : entidades)
        if (e == entidad)
            return true;
    return false;
}

bool Sistema_particulas::hay_entidad(Entidad *entidad, std::vector<Particula *> entidades)
{
    for (Particula *p : entidades)
        if (p == entidad)
            return true;
    return false;
}

void Sistema_particulas::recursividad(Entidad *entidad, std::vector<Entidad *> &entidades, QuadTree &qt, Grafo &grafo)
{
    entidades.push_back(entidad);
    c_particulas.push_back((Particula *)entidad);

    std::vector<Entidad *> vecinos;
    qt.buscar(((Particula *)entidad)->c_estructura, vecinos);
    grafo.agregar_vertice(entidad, vecinos);

    for (Entidad *e : vecinos)
        if (!hay_entidad(e, entidades))
            recursividad(e, entidades, qt, grafo);
}

void Sistema_particulas::crear_grafo(Particula *particula, QuadTree &qt)
{
    std::vector<Entidad *> particulas;
    Grafo grafo;

    recursividad(particula, particulas, qt, grafo);

    c_grafos.push_back(grafo);
}

void recursivo_dos(Vertice &vertice, Grafo &sistema, const float dt)
{
    Particula *particula = (Particula *)vertice.c_clave;
    Vector2 fuerza = particula->c_fuerza + (particula->c_vel * particula->c_masa) / dt;

    // for (std::pair<Entidad *, Vector2> par : vertice.c_vecinos)
    // {
    // }
}

void Sistema_particulas::aplicar_fuerzas(const float dt)
{
    for (Grafo &sistema : c_grafos)
    {
        // std::vector<Vertice> maximos;
        // sistema.encontrar_maximos(maximos);

        // for (Vertice vertice : maximos)
        //     recursivo_dos(vertice, sistema, dt);
    }
}
