#pragma once

#include <vector>

#include "../vector.h"
#include "../cuerpos/gjk.h"
#include "fuerzas.h"
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
        std::vector<Intercambio *> m_fuerzas;

    protected:
        bool m_es_estatico;

    public:
        Particula(cr::InfoCuerpo *info, Vector2 velocidad, float velocidad_angular, float coeficiente);
        Particula(cr::InfoCuerpo *info);

        void agregar_interaccion(Particula *referencia);
        bool expandir();
        void actualizar();

        void aplicar_fuerza(Intercambio *fuerza);
        // void aplicar_torque(float torque);
        // void aplicar_fuerza(Vector2 fuerza);

    private:
        // bool choque_de_fuerzas(Particula *particula, Vector2 &normal, Caracteristica impacto);
        // bool choque_de_velocidades(Particula *particula, Vector2 &normal, Caracteristica impacto);

        // void rotacion_por_choque(Vector2 fuerza, Caracteristica impacto);

        // Vector2 fuerza_de_choque(Particula *particula, Vector2 &direccion);
        // Vector2 velocidad_en_direccion(Vector2 &direccion);
    };

    class Intercambio
    {
    protected:
        Vector2 m_magnitud;

    public:
        Intercambio(Vector2 magnitud);

        virtual void aplicar(Vector2 direccion, Particula *particula) = 0;
    };

    class Velocidad : public Intercambio
    {
    public:
        Velocidad(Vector2 magnitud);

        void aplicar(Vector2 direccion, Particula *particula) override;
    };

    class Fuerza : public Intercambio
    {
    public:
        Fuerza(Vector2 magnitud);

        void aplicar(Vector2 direccion, Particula *particula) override;
        Intercambio *en_dir(Vector2 direccion);
    };

    class VelocidadAngular : public Intercambio
    {
    public:
        VelocidadAngular(Vector2 magnitud);

        void aplicar(Vector2 direccion, Particula *particula) override;
    };

    class Torque : public Intercambio
    {
    public:
        Torque(Vector2 magnitud);

        void aplicar(Vector2 direccion, Particula *particula) override;
    };
}