#pragma once

#include <vector>

#include "../herramientas/quadtree.h"
#include "../herramientas/area.h"
#include "../herramientas/vector.h"
#include "../herramientas/grafo.h"

#include "particula.h"

class Fisicas
{
private:
    QuadTree c_qt;
    std::vector<Particula *> c_particulas;
    Vector2 gravedad;

public:
    Fisicas(const Rectangulo &mundo);
    ~Fisicas();

    bool insertar_particula(Particula *particula);

    void avanzar(const float dt);
    void resolverColisiones(const float dt);

private:
    bool lugar_libre(const Particula *particula);
};

class Sistema_particulas
{
private:
    std::vector<Grafo> c_grafos;
    std::vector<Particula *> c_particulas;

public:
    Sistema_particulas(std::vector<Particula *> &particulas, QuadTree &qt);

    void crear_grafo(Particula *particula, QuadTree &qt);
    void recursividad(Entidad *entidad, std::vector<Entidad *> &entidades, QuadTree &qt, Grafo &grafo);
    void aplicar_fuerzas(const float dt);

private:
    bool hay_entidad(Entidad *entidad, std::vector<Entidad *> entidades);
    bool hay_entidad(Entidad *entidad, std::vector<Particula *> entidades);
};
