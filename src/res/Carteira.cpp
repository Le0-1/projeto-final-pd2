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
    this->_transacoes.insert(std::pair<int, Transacao>(transacao.getID(), transacao));
}

void Carteira::removerTransacao(int id) {
    this->_transacoes.erase(id);
}

std::map<int, Transacao> Carteira::ultimasTransacoes(unsigned int quantidade) {
    std::map<int, Transacao> ultimas_transacoes;

    for (auto const& transacao : this->_transacoes) {
        ultimas_transacoes.insert(std::pair<int, Transacao>(transacao.first, transacao.second));
        quantidade--;
        if (quantidade <= 0) break;
    }

    return ultimas_transacoes;
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