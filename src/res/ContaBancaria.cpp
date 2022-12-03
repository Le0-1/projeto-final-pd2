#include "ContaBancaria.hpp"

#include <iostream>

ContaBancaria::ContaBancaria(std::string nome, double saldo_inicial)
    : Carteira(nome, saldo_inicial, "ContaBancaria") { }

void ContaBancaria::adicionarCartao(CartaoDeCredito cartao) {
    getCartoes().insert(std::pair<std::string, CartaoDeCredito>(cartao.getNome(), cartao));
}

ContaBancaria::~ContaBancaria() { }

void ContaBancaria::removerCartao(std::string nome) {
    if (this->_cartoes.find(nome) == this->_cartoes.end()){
        throw cdcexcp::CartaoNaoEncontrado(nome);
    }
    getCartoes().erase(getCartoes().find(nome));
}

std::map<std::string, CartaoDeCredito> &ContaBancaria::getCartoes() {
    return this->_cartoes;
}

CartaoDeCredito *ContaBancaria::getCartaoDeCredito(std::string nome) {
    if (getCartoes().find(nome) == getCartoes().end()) {
        throw cdcexcp::CartaoNaoEncontrado(nome);
    }
    return &getCartoes().find(nome)->second;
}

void ContaBancaria::pagarFatura(std::string cartao) {
    CartaoDeCredito *cartaoDeCredito = getCartaoDeCredito(cartao);
    setSaldoAtual(getSaldoAtual() - cartaoDeCredito->getTotalDespesas());

    std::list<std::shared_ptr<Despesa>>* listDespesa = cartaoDeCredito->getListaDespesas();
    for (std::shared_ptr<Despesa> despesa : *listDespesa) {

        int id = despesa->getID();
        getTransacoes().insert(std::pair<int, std::shared_ptr<Transacao>>(id, despesa));
    }

    listDespesa->clear();
}

void ContaBancaria::imprimirInfo() {
    const std::string separador = "___________________________________________";
    Utils::printColor(Foreground::f_yellow, separador);

    std::cout << getSubtipo() << ": " << getNome() << std::endl;
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
    ultimasTransacoes(3);

    std::cout << "Quantidade de cartoes: " << getCartoes().size() << std::endl;
    imprimirCartoes();

    Utils::printColor(Foreground::f_yellow, separador);
}

void ContaBancaria::imprimirCartoes() {

    for (auto &it : getCartoes()) {
        std::cout << std::endl;
        it.second.imprimirInfo();
    }
}