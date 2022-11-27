#include "ContaBancaria.hpp"

#include <iostream>

ContaBancaria::ContaBancaria(std::string nome, double saldo_inicial)
    : Carteira(nome, saldo_inicial, "ContaBancaria") { }

void ContaBancaria::adicionarCartao(CartaoDeCredito cartao) {
    getCartoes().insert(std::pair<std::string, CartaoDeCredito>(cartao.getNome(), cartao));
}

ContaBancaria::~ContaBancaria() { }

void ContaBancaria::removerCartao(std::string nome) {
    getCartoes().erase(getCartoes().find(nome));
}

std::map<std::string, CartaoDeCredito> &ContaBancaria::getCartoes() {
    return this->_cartoes;
}

CartaoDeCredito &ContaBancaria::getCartaoDeCredito(std::string nome) {
    return getCartoes().find(nome)->second;
}

void ContaBancaria::imprimirCartoes() {
    std::map<std::string, CartaoDeCredito>::iterator it;
    for (it = getCartoes().begin(); it != getCartoes().end(); ++it) {
        std::cout << it->second.getNome() << std::endl;
    }
}