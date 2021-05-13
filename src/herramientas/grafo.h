#pragma once

#include "vector.h"
#include "entidad.h"
#include <vector>

class Grafo;

class Vertice
{
public:
    Entidad *c_clave;
    std::vector<Vertice> c_vecinos;
    void *c_padre;

public:
    Vertice(Grafo *grafo, Entidad *clave);
    Vertice(Grafo *grafo, Entidad *clave, std::vector<Entidad *> &vecinos);
};

class Grafo
{
public:
    std::vector<Vertice> c_vertices;

public:
    Vertice vertice_por_clave(Entidad *clave);
    void agregar_vertice(Entidad *clave, std::vector<Entidad *> &vecinos);
    void agregar_vertice(Entidad *clave);
};
