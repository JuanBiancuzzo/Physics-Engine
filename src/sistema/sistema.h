#pragma once

#include <vector>
#include <memory>

#include "../vector.h"
#include "../cuerpos/gjk.h"
#include "historial.h"

namespace sistema
{
    class Particula;
    class Interaccion;
    class Intercambio;

    class Sistema
    {
    private:
        std::vector<Particula *> m_particulas;

    public:
        Sistema(std::vector<Particula *> particulas);

        void agregar_interaccion(Particula *particula, Particula *referencia);
        void expandir_interacciones();
    };

    struct Interaccion
    {
        Particula *particula;
        Vector2 normal;
        Caracteristica impacto;
    };

    class Particula : public Historial<Particula *>
    {
    public:
        cr::InfoCuerpo *m_info;
        float m_coeficiente;
        Vector2 m_velocidad;
        float m_velocidad_angular;
        std::vector<Interaccion> m_interacciones;
        std::vector<std::pair<Intercambio *, bool>> m_fuerzas;
        bool m_es_estatico;

    public:
        Particula(cr::InfoCuerpo *info, Vector2 velocidad, float velocidad_angular, float coeficiente);
        Particula(cr::InfoCuerpo *info);
        ~Particula();

        void agregar_interaccion(Particula *referencia);
        bool expandir();
        void actualizar();
        void velocidad_final();

        void aplicar_fuerza(Intercambio *fuerza);
        void aplicar_fuerza(Intercambio *fuerza, bool alocado);

        Vector2 fuerza_de_choque(Particula *particula, Vector2 &direccion);
    };

    class Intercambio
    {
    public:
        ~Intercambio();

        virtual bool aplicar(Vector2 direccion, Particula *particula, Particula *referencia) = 0;
        virtual void actualizar() = 0;
        virtual void modificar(Vector2 &velocidad, float &velocidad_angular, cr::InfoCuerpo *info) = 0;
    };

    class MagnitudVectorial : public Intercambio
    {
    protected:
        Vector2 m_magnitud;
        Vector2 m_magnitud_reservada;

    public:
        MagnitudVectorial(Vector2 magnitud);

        void actualizar() override;
        void reservar_magnitud(Vector2 magnitud_nueva);
    };

    class MagnitudEscalar : public Intercambio
    {
    protected:
        float m_magnitud;
        float m_magnitud_reservada;

    public:
        MagnitudEscalar(float magnitud);

        void actualizar() override;
        void reservar_magnitud(float magnitud_nueva);
    };

    class Velocidad : public MagnitudVectorial
    {
    public:
        Velocidad(Vector2 magnitud);

        bool aplicar(Vector2 direccion, Particula *particula, Particula *referencia) override;
        void modificar(Vector2 &velocidad, float &velocidad_angular, cr::InfoCuerpo *info) override;
    };

    class Fuerza : public MagnitudVectorial
    {
    public:
        Fuerza(Vector2 magnitud);

        bool aplicar(Vector2 direccion, Particula *particula, Particula *referencia) override;
        void modificar(Vector2 &velocidad, float &velocidad_angular, cr::InfoCuerpo *info) override;
        Intercambio *en_dir(Vector2 direccion);
    };

    class VelocidadAngular : public MagnitudEscalar
    {
    public:
        VelocidadAngular(float magnitud);

        bool aplicar(Vector2 direccion, Particula *particula, Particula *referencia) override;
        void modificar(Vector2 &velocidad, float &velocidad_angular, cr::InfoCuerpo *info) override;
    };

    class Torque : public MagnitudEscalar
    {
    public:
        Torque(float magnitud);

        bool aplicar(Vector2 direccion, Particula *particula, Particula *referencia) override;
        void modificar(Vector2 &velocidad, float &velocidad_angular, cr::InfoCuerpo *info) override;
    };
}