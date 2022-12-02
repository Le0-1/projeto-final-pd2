#ifndef TRANSACAO_EXCP_H
#define TRANSACAO_EXCP_H

#include <exception>
#include <string>

namespace trsexcp {

    class TransacaoNaoEncontrada : public std::exception {
        private:
            int _id;

        public:
            TransacaoNaoEncontrada(int id);

            const char* what() const throw();

            int getID();
    };

    class TipoTransacaoInvalido : public std::exception {
        private:
            std::string _tipo;

        public:
            TipoTransacaoInvalido(std::string tipo);

            const char* what() const throw();

            std::string getTipo();
    };
}

#endif
