#include "grafo.h"

Vertice::Vertice(Grafo *grafo, Entidad *clave)
    : c_clave(clave), c_padre(grafo)
{
}

Vertice::Vertice(Grafo *grafo, Entidad *clave, std::vector<Entidad *> &vecinos)
    : c_clave(clave), c_padre(grafo)
{
    c_vecinos.reserve(vecinos.size());

    for (Entidad *entidad : vecinos)
        c_vecinos.emplace_back(grafo->vertice_por_clave(clave));
}

Vertice Grafo::vertice_por_clave(Entidad *clave)
{
    for (Vertice &vertice : c_vertices)
        if (vertice.c_clave == clave)
            return vertice;
    c_vertices.push_back(Vertice(this, clave));
    return c_vertices[0];
}

void Grafo::agregar_vertice(Entidad *clave, std::vector<Entidad *> &vecinos)
{
    c_vertices.push_back(Vertice(this, clave, vecinos));
}

void Grafo::agregar_vertice(Entidad *clave)
{
    c_vertices.push_back(Vertice(this, clave));
}
