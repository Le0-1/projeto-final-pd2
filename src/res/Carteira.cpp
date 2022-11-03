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

void Carteira::AdicionarTransacao(Transacao t) {
    this->transacoes.insert(std::pair<int, Transacao>(t.GetID(), t));
}

void Carteira::RemoverTransacao(Transacao t) {
    this->transacoes.erase(t.GetID());
}

std::map<int, Transacao> Carteira::UltimasTransacoes(int quantidade) {
    std::map<int, Transacao> aux;

    if (this->transacoes.size() < quantidade) quantidade = this->transacoes.size();
    
    for (int i = 0; i < quantidade; i++) {
        aux.insert(std::pair<int, Transacao>(this->transacoes[i].GetID(), this->transacoes[i]));
    }

    return aux;
}

std::string Carteira::GetNome() {
    return this->_nome;
}

double Carteira::GetSaldoAtual() {
    return this->_saldo_atual;
}

double Carteira::GetSaldoInicial() {
    return this->_saldo_inicial;
}
