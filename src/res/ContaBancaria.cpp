#include "ContaBancaria.hpp"

#include <iostream>

ContaBancaria::ContaBancaria() {};

void ContaBancaria::adicioanarCartao(Cartao cartao) {
    this->_cartoes.insert(std::pair<std::string, Cartao>(cartao.getNome(), cartao));
}

void ContaBancaria::removerCartao(Cartao cartao) {
    this->_cartoes.erase(cartao.getNome());
}

void ContaBancaria::imprimirCartoes() {
    std::map<std::string, Cartao>::iterator it;
    for(it = this->_cartoes.begin(); it != this->_cartoes.end(); ++it) {
        std::cout << it->second.getNome() << std::endl;
    }
}