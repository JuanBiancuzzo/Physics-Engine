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

    void mostrar() const;
    void avanzar(const float dt);
    void resolverColisiones(const float dt);

private:
    bool lugar_libre(const Particula *particula);
};
