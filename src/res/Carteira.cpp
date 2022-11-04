#include "Carteira.hpp"

Carteira::Carteira(double saldo_inicial, std::string nome, double saldo_atual) {
    this->_nome = nome;
    this->_saldo_inicial = saldo_inicial;
    this->_saldo_atual = saldo_atual;
}

Carteira::Carteira(std::string nome) {
    this->_nome = nome;
    this->_saldo_inicial = 0;
    this->_saldo_atual = 0;
}

void Carteira::adicionarTransacao(Transacao t) {
    this->transacoes.insert(std::pair<int, Transacao>(t.getID(), t));
}

void Carteira::removerTransacao(Transacao t) {
    this->transacoes.erase(t.getID());
}

std::map<int, Transacao> Carteira::ultimasTransacoes(unsigned quantidade) {
    std::map<int, Transacao> aux;

    for (auto it : this->transacoes) {
        aux.insert(std::pair<int, Transacao>(it.first, it.second));
        quantidade--;
        if (quantidade <= 0) break;
    }

    return aux;
}

std::string Carteira::getNome() {
    return this->_nome;
}

double Carteira::getSaldoAtual() {
    return this->_saldo_atual;
}

double Carteira::getSaldoInicial() {
    return this->_saldo_inicial;
}
