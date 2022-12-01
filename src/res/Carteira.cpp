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

void Carteira::adicionarTransacao(std::shared_ptr<Transacao> transacao) {
    this->_transacoes.insert(std::pair<int, std::shared_ptr<Transacao>>
        (transacao->getID(), transacao));
}

void Carteira::removerTransacao(int id) {
    this->_transacoes.erase(id);
}

std::map<int, std::shared_ptr<Transacao>> Carteira::ultimasTransacoes(unsigned int quantidade) {
    std::map<int, std::shared_ptr<Transacao>> ultimas_transacoes;

    for (auto &transacao : getTransacoes()) {
        ultimas_transacoes.insert(std::pair<int, std::shared_ptr<Transacao>>
            (transacao.first, transacao.second));
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

std::map<int, std::shared_ptr<Transacao>>& Carteira::getTransacoes() {
    return this->_transacoes;
}

std::string Carteira::getSubtipo() {
    return this->_subtipo;
}

void Carteira::imprimirInfo() {
    const std::string separador = "___________________________________________";

    Utils::printColor(Foreground::f_yellow, separador);

    std::cout << getSubtipo() <<": " << getNome() << std::endl;

    std::cout << "Saldo atual: ";
    std::cout << std::fixed << std::setprecision(2);

    std::string saldo = std::to_string(getSaldoAtual());
    saldo = "R$ " + saldo.substr(0, saldo.find(".") + 3);

    if (getSaldoAtual() > 0) {
        Utils::printColor(Foreground::f_green, saldo);
    }
    else if (getSaldoAtual() < 0) {
        Utils::printColor(Foreground::f_red, saldo);
    }
    else {
        std::cout << saldo << std::endl;
    }

    std::cout << "Quantidade de transacoes: " << getTransacoes().size() << std::endl;

    Utils::printColor(Foreground::f_yellow, separador);
}