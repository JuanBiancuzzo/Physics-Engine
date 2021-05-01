#pragma once

#include <vector>

#include "../herramientas/quadtree.h"
#include "../herramientas/area.h"
#include "../herramientas/vector.h"

#include "particula.h"

struct Colision
{
    Particula *A;
    Particula *B;

    Colision(Particula *a, Particula *b)
        : A(a), B(b)
    {
    }
};

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
