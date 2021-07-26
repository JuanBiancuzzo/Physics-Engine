#pragma once

#include "../vector.h"

namespace cr
{
    class Arista;
    class Vertice;

    class Caracteristcia
    {
    public:
        Caracteristcia *intersecta(Caracteristcia *caracteristcia);

        virtual Caracteristcia *intersecta(Arista *arista) = 0;
        virtual Caracteristcia *intersecta(Vertice *vertice) = 0;
    };

    class Arista : public Caracteristcia
    {
    private:
        Vector2 m_principal, m_final;

    public:
        Arista(Vector2 inicio, Vector2 final);

        Caracteristcia *intersecta(Arista *arista);
        Caracteristcia *intersecta(Vertice *vertice);
    };

    class Vertice : public Caracteristcia
    {
    public:
        Vector2 m_vertice;

    public:
        Vertice(Vector2 punto);

        Arista crear_arista(Vector2 final);
        Caracteristcia *intersecta(Arista *arista);
        Caracteristcia *intersecta(Vertice *vertice);
    };
}