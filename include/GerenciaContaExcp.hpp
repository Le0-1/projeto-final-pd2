#ifndef GERENCIA_CONTA_EXCP_H
#define GERENCIA_CONTA_EXCP_H

#include <exception>
#include <string>

namespace gcexcp {

    class ValorInvalido : public std::exception {
        private:
            double _valor;
            std::string _nome;

        public:
            ValorInvalido(double valor, std::string nome);

            const char* what() const throw();

            double getValor();

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

    class ContaNaoPermiteCartao : public std::exception {
        public:
            std::string _nome_conta, _subtipo_conta;

        public:
            ContaNaoPermiteCartao(std::string nome_conta, std::string tipo_conta);

            const char * what() const throw();

            std::string getNomeConta();

            std::string getSubtipoConta();
    };
}

#endif
