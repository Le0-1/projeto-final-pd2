#ifndef CARTEIRA_H
#define CARTEIRA_H

#include "Transacao.hpp"

#include <string>
#include <map>
#include <utility>

class Carteira {
    private:
        std::string _nome;
        double _saldo_inicial, _saldo_atual;
        std::map<int, Transacao> transacoes;

    public:
        Carteira(double saldo_inicial, std::string nome,  double saldo_atual);

        Carteira(std::string nome);

        std::map<int, Transacao> ultimasTransacoes(unsigned quantidade);

        void adicionarTransacao(Transacao t);

        void removerTransacao(Transacao t);

        std::string getNome();

        double getSaldoInicial();
        
        double getSaldoAtual();
};

#endif // !CARTEIRA
