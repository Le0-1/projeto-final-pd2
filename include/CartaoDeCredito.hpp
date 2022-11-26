#ifndef CARTAO_DE_CREDITO_H
#define CARTAO_DE_CREDITO_H

#include "Despesa.hpp"
#include "CartaoDeCreditoExcp.hpp"

#include <string>
#include <list>
#include <memory>
#include <iostream>

class CartaoDeCredito {
    private:
        std::string _nome, _numero, _CVV, _fechamento;
        double _limite_cartao;
        std::list<std::shared_ptr<Despesa>> _lista_de_despesas;

    public:
        CartaoDeCredito(std::string nome, std::string numero, std::string CVV,
                        std::string fechamento, double limite_cartao);

        std::string getNome();

        std::string getNumero();

        std::string getFechamento();

        double getTotalDespesas();

        double getLimite();

        std::list<std::shared_ptr<Despesa>>& getListaDeDespesas();

        void alterarLimiteCartao(double limite);

        void adicionarDespesa(double valor, std::string data, std::string categoria);

        void listarDespesas();

        // Retorna true se a despesa foi localizada e removida
        // e falso se nao foi localizada
        bool removerDespesa(int id);
};

#endif
