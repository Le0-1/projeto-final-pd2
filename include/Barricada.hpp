#ifndef BARRICADA_H
#define BARRICADA_H

#include <iostream>
#include <limits>

namespace Barrier {

    class Barricada {
        public:
            void validar_saldo(double &saldo);

            void validar_input(unsigned &input);

            void validar_transacao(double &valor_transacao);

            void validar_id(unsigned &id);

            void validar_limite_cartao(double &limite);

    };

}


#endif