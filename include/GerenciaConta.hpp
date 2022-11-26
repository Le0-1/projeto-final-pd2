#ifndef GERENCIA_CONTA_H
#define GERENCIA_CONTA_H

#include "Transferencia.hpp"
#include "Carteira.hpp"
#include "ContaBancaria.hpp"
#include "Receita.hpp"
#include "Despesa.hpp"
#include "Transferencia.hpp"
#include "CartaoDeCredito.hpp"

#include <memory>
#include <map>

class GerenciaConta {
    private:
        std::map<std::string, std::shared_ptr<Carteira>> _contas;
        std::map<int, Transferencia> _transferencias;

    public:
        GerenciaConta();

        std::map<std::string, std::shared_ptr<Carteira>>& getContas();

        std::map<int, Transferencia> &getTransferencias();

        std::shared_ptr<Carteira> getConta(std::string nome);

        void adicionarCarteira(std::string nome, double saldo_inicial);

        void adicionarConta(std::string nome, double saldo_inicial);

        void removerConta(std::string nome);

        void adicionarReceita(std::string conta, double valor, std::string data,
            std::string categoria);

        void adicionarDespesa(std::string conta, double valor, std::string data,
            std::string categoria);

        void adicionarDespesaCartao(std::string conta,std::string cartao, double valor, std::string data,
            std::string categoria);

        void adicionarTransferencia(double valor, std::string data, std::string categoria,
            std::string origem, std::string destino);

        void removerReceita(std::string conta, int id);

        void removerDespesa(std::string conta, int id);

        void removerDespesaCartao(std::string conta, std::string cartao, int id);

        void removerTransferencia(int id);

        void adicionarCartao(std::string conta, std::string nome,
            std::string numero, std::string CVV, std::string fechamento, double limite_cartao);

        void removerCartao(std::string conta, std::string cartao);

        void pagarFatura(std::string conta, std::string cartao);

        void imprimirContas();
};

#endif