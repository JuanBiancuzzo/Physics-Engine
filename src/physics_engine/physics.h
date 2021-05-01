#pragma once

#include <vector>

#include "../herramientas/quadtree.h"
#include "../herramientas/area.h"
#include "../herramientas/vector.h"

#include "body.h"

class Fisicas
{
private:
    QuadTree c_qt;
    std::vector<Body *> c_bodys;

public:
    Fisicas(const Rectangulo &mundo);
    ~Fisicas();

    bool insertar_particula(Body *body);

    void mostrar() const;
    void avanzar(const float delta_tiempo);

private:
    bool lugar_libre(const Body *body);
};
