#pragma once

#include <vector>

#include "quadtree.h"
#include "particula.h"
#include "rectangulo.h"
#include "vector.h"

class Fisicas
{
private:
    QuadTree c_qt;
    std::vector<Particula *> c_particulas;

public:
    Fisicas(const Rectangulo &mundo);
    ~Fisicas();

    void insertar_particula(const Particula &particula);
    void insertar_particula(const Vector2 &pos);

    void mostrar() const;
    void avanzar(const float delta_tiempo);
};
