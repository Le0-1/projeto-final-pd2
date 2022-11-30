#ifndef TRANSACAO_EXCP_H
#define TRANSACAO_EXCP_H

#include <exception>

namespace trexcp {

    class TransacaoNaoEncontrada : public std::exception {
        private:
            int _id;

        public:
            TransacaoNaoEncontrada(int id);

            const char* what() const throw();

            int getID();
    };
}

#endif