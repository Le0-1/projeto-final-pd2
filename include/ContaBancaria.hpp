#ifndef CONTABANCARIA_H
#define CONTABANCARIA_H

#include "Carteira.hpp"
#include "CartaoDeCredito.hpp"

#include <string>
#include <map>

class ContaBancaria : public Carteira {
    private:
      std::map<std::string, CartaoDeCredito> _cartoes;

    public:
        ContaBancaria(std::string nome, double saldo_inicial);

        ~ContaBancaria();

        void adicionarCartao(CartaoDeCredito cartao);

        void removerCartao(std::string nome);

        std::map<std::string, CartaoDeCredito> &getCartoes();

        CartaoDeCredito &getCartaoDeCredito(std::string nome);

        void imprimirCartoes();
};

#endif