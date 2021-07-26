#include "caracteristica.h"

using namespace cr;

Caracteristcia *Caracteristcia::intersecta(Caracteristcia *caracteristcia)
{
    caracteristcia->intersecta(this);
}

Arista::Arista(Vector2 inicio, Vector2 final)
    : m_principal(inicio), m_final(final)
{
}

Caracteristcia *Arista::intersecta(Arista *arista)
{
}

Caracteristcia *Arista::intersecta(Vertice *vertice)
{
    return new Vertice(vertice->m_vertice);
}

Vertice::Vertice(Vector2 punto)
    : m_vertice(punto)
{
}

Arista Vertice::crear_arista(Vector2 final)
{
    return Arista(m_vertice, final);
}

Caracteristcia *Vertice::intersecta(Arista *arista)
{
    return new Vertice(m_vertice);
}

Caracteristcia *Vertice::intersecta(Vertice *vertice)
{
    Vector2 promedio = (m_vertice + vertice->m_vertice) / 2;
    return new Vertice(promedio);
}