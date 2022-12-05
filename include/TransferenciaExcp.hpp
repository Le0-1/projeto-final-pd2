#ifndef TRANSFERENCIA_EXCP_H
#define TRANSFERENCIA_EXCP_H

#include <iostream>
#include <exception>

namespace trfexcp {  
    
    class TransferenciaInvalida : public std::exception {
        private:
            std::string _nome_da_conta;

        public:
            TransferenciaInvalida(std::string);

            const char* what() const throw();

            std::string getNomeConta();
    };
}

#endif