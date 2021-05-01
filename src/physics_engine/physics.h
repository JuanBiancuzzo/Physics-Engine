#pragma once

#include <vector>

#include "../herramientas/quadtree.h"
#include "../herramientas/area.h"
#include "../herramientas/vector.h"

#include "body.h"

struct Colision
{
    Body *A;
    Body *B;
};

class Fisicas
{
private:
    QuadTree c_qt;
    std::vector<Body *> c_bodys;
    Vector2 gravedad;

public:
    Fisicas(const Rectangulo &mundo);
    ~Fisicas();

    bool insertar_particula(Body *body);

    void mostrar() const;
    void avanzar(const float dt);
    void resolverColisiones(const float dt);

private:
    bool lugar_libre(const Body *body);
};
