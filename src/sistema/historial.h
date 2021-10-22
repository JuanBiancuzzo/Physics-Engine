#pragma once

#include <vector>

namespace sistema
{
    template <typename T>
    class Historial
    {
    private:
        std::vector<T> m_historial;

    public:
        void agregar_elemento(T elemento)
        {
            m_historial.emplace_back(elemento);
        }

        bool en_historial(T elemento)
        {
            for (T e : m_historial)
                if (e == elemento)
                    return true;
            return false;
        }

        void resetear()
        {
            m_historial.clear();
        }
    };
}