#ifndef CARTAO_DE_CREDITO_EXCP_H
#define CARTAO_DE_CREDITO_EXCP_H

#include <exception>
#include <string>

namespace cdcexcp {

    class LimiteExcedido : public std::exception {
        private:
            std::string _nome_cartao, _numero_cartao;
            double _limite_cartao, _soma_despesas_atuais;

        public:
            LimiteExcedido(std::string nome_cartao, std::string numero_cartao,
                           double limite_cartao, double soma_despesas_atuais);

            const char* what() const throw();

            std::string getNomeCartao();

            std::string getNumeroCartao();

            double getLimiteCartao();

            double getSomaDespesasAtuais;
    };

    class LimiteInvalido : public std::exception {
        private:
            std::string _nome_cartao, _numero_cartao;
            double _limite_cartao;

        public:
            LimiteInvalido(std::string nome_cartao, std::string numero_cartao, double limite_cartao);

            const char* what() const throw();

            std::string getNomeCartao();

            std::string getNumeroCartao();

            double getLimiteCartao();
    };

    class CartaoNaoEncontrado : public std::exception {
        private:
            std::string _nome_cartao;

        public:
            CartaoNaoEncontrado(std::string nome_cartao);

            const char* what() const throw();

            std::string getNomeCartao();
    };
}

#endif // !CARTAO_DE_CREDITO_EXCP_H
