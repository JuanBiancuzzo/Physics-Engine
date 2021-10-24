#pragma once

namespace sistema
{
    template <typename T>
    class ValorReservado
    {
    private:
        T m_valor, m_reservado;
    
    public:
        ValorReservado(T valor_inicial)
            : m_valor(valor_inicial), m_reservado(valor_inicial)
        {
        }


        void nuevo_valor(T valor_nuevo)
        {
            m_reservado += valor_nuevo;
        }

        T valor()
        {
            return m_valor;
        }

        void actualizar()
        {
            m_valor = m_reservado;
        }
    };
}