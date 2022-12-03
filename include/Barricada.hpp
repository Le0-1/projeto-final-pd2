#ifndef BARRICADA_H
#define BARRICADA_H

#include <iostream>
#include <limits>

class Barricada {
    public:
        static void validar_saldo(double &saldo);

        static void validar_input(unsigned &input);

        static void validar_transacao(double &valor_transacao);

        static void validar_id(unsigned &id);

        static void validar_limite_cartao(double &limite);
};

#endif