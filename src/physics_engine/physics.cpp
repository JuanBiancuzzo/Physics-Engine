#include "headers/physics.h"

// Fisicas::Fisicas(const Rectangulo &mundo)
//     : c_qt(mundo), c_cantidad(0)
// {
// }

// Fisicas::~Fisicas()
// {
//     for (Particula *particula : c_particulas)
//         delete particula;
// }

// bool Fisicas::lugar_libre(const Particula &particula)
// {
//     float r = particula.c_radio;
//     return !c_qt.cantidad(Rectangulo(particula.c_pos, r * 2, r * 2));
// }

// bool Fisicas::insertar_particula(const Particula *particula)
// {
//     if (!lugar_libre(*particula))
//         return false;

//     c_qt.insertar(particula);
//     c_particulas.emplace_back(particula);
//     c_cantidad++;
//     return true;
// }

// void Fisicas::mostrar() const
// {
//     // cuando tenga una forma de renderizas aca deberia estar
// }

// void Fisicas::avanzar(const float delta_tiempo)
// {
//     // c_particulas esta ordenado de mayor velocidad a menor velocidad - aka un heap
//     for (Particula *particula : c_particulas)
//     {
//         // calcular fuerzas
//         /*
//              * rozamiento
//              * interacciones con otros objetos
//              * futuras otras fuerzas
//              */
//         // particula->aplicar_fuerza();
//         // hacer un cache si la velocidad se hace muy grande
//     }

//     for (Particula *particula : c_particulas)
//     {
//         particula->actualizar(delta_tiempo);
//         c_qt.actualizar(*particula);
//     }
// }