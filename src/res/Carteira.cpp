#include "Carteira.hpp"

Carteira::Carteira(std::string nome, double saldo_inicial) {
    this->_nome = nome;
    this->_saldo_atual = saldo_inicial;
    this->_subtipo = "Carteira";
}

Carteira::Carteira(std::string nome, double saldo_inicial, std::string subtipo) {
    this->_nome = nome;
    this->_saldo_atual = saldo_inicial;
    this->_subtipo = subtipo;
}

Carteira::~Carteira() { }

void Carteira::adicionarTransacao(Transacao transacao) {
    this->transacoes.insert(std::pair<int, Transacao>(transacao.getID(), transacao));
}

void Carteira::removerTransacao(int id) {
    this->transacoes.erase(id);
}

std::map<int, Transacao> Carteira::ultimasTransacoes(unsigned int quantidade) {
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

void Carteira::setSaldoAtual(double saldo) {
    this->_saldo_atual = saldo;
}

std::string Carteira::getSubtipo() {
    return this->_subtipo;
}