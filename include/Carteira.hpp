#ifndef CARTEIRA_H
#define CARTEIRA_H

#include "Transacao.hpp"

#include <string>
#include <map>

class Carteira {
    private:
        std::string _nome;
        double _saldo_atual;
        std::map<int, Transacao> _transacoes;
        std::string _subtipo;

    public:
        Carteira(std::string nome, double saldo_inicial);

        Carteira(std::string nome, double saldo_inicial, std::string subtipo);

        virtual ~Carteira();

        std::map<int, Transacao> ultimasTransacoes(unsigned int quantidade);

        void adicionarTransacao(Transacao transacao);

        void removerTransacao(int id);

        std::string getNome();

        double getSaldoAtual();

        void setSaldoAtual(double saldo);

        std::string getSubtipo();
};

#endif 