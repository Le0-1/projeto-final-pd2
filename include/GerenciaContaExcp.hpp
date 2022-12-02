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

    class ContaNaoEncontrada : public std::exception {
        private:
            std::string _nome;

        public:
            ContaNaoEncontrada(std::string nome);

            const char* what() const throw();

            std::string getNome();
    };

    class PerfilVazio : public std::exception {
        public:
            PerfilVazio();

            const char* what() const throw();
    };

    class ContaJaExiste : public std::exception {
        public:
            std::string _nome;

        public:
            ContaJaExiste(std::string nome);

            const char* what() const throw();

            std::string getNome();
    };
}

#endif
