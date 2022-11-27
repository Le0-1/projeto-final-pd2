#ifndef GERENCIA_CONTA_EXCP_H
#define GERENCIA_CONTA_EXCP_H

#include <exception>
#include <string>

namespace gcexcp {

    class SaldoInvalido : public std::exception {
        private:
            double _saldo_inicial;
            std::string _nome;

        public:
            SaldoInvalido(double saldo_inicial, std::string nome);

            const char* what() const throw();

            double getSaldoInicial();

            std::string getNome();


    };
}

#endif