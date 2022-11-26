#include "CartaoDeCreditoExcp.hpp"

LimiteExcedido::LimiteExcedido(std::string nome_cartao, std::string numero_cartao,
                               double limite_cartao) {
    this->_nome_cartao = nome_cartao;
    this->_numero_cartao = numero_cartao;
    this->_limite_cartao = limite_cartao;
}

const char* LimiteExcedido::what() const throw() {
    return "Limite do cartao excedido";
}

std::string LimiteExcedido::getNomeCartao() {
    return this->_nome_cartao;
}

std::string LimiteExcedido::getNumeroCartao() {
    return this->_numero_cartao;
}

double LimiteExcedido::getLimiteCartao() {
    return this->_limite_cartao;
}
