#pragma once

#include "sistema.h"
#include "../cuerpos/gjk.h"
#include "fuerza.h"

namespace sistema
{
    class Interaccion;
    class Fuerza;

    class Particula : public Historial<Particula *>
    {
    protected:
        cr::CuerpoRigido *m_cuerpo;

    public:
        std::vector<std::unique_ptr<Fuerza>> m_fuerzas;
        std::vector<Interaccion> m_interacciones;

    public:
        Particula(cr::CuerpoRigido *cuerpo);
        virtual ~Particula() = default;

        void aplicar_fuerza(std::unique_ptr<Fuerza> &fuerza);
        void agregar_interaccion(Particula *referencia);

        virtual bool expandir() = 0;
        virtual void actualizar() = 0;
        virtual bool puede_interactuar(Particula *referencia) = 0;

        virtual Vector2 velocidad() = 0;
        virtual float velocidad_angular() = 0;
    };

    class ParticulaDinamica : public Particula
    {
    public:
        cr::InfoCuerpo *m_info;
        float m_coeficiente;

    public:
        ParticulaDinamica(cr::InfoCuerpo *info, Vector2 velocidad, float velocidad_angular, float coeficiente);

        bool expandir() override;
        void actualizar() override;
        bool puede_interactuar(Particula *referencia) override;

        Vector2 velocidad() override;
        float velocidad_angular() override;

        Vector2 fuerza_de_choque(Particula *particula, Vector2 &direccion);
    };

    class ParticulaEstatica : public Particula
    {
    public:
        ParticulaEstatica(cr::CuerpoRigido *cuerpo);

        bool expandir() override;
        void actualizar() override;
        bool puede_interactuar(Particula *referencia) override;

        Vector2 velocidad() override;
        float velocidad_angular() override;
    };
}