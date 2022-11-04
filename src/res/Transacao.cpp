#include "Transacao.hpp"

int Transacao::_contador = 0;

Transacao::Transacao(double valor, std::string descricao, std::string data, 
        std::string categoria) {
    this->_valor = valor;
    this->_descricao = descricao;
    this->_data = data;
    this->_categoria = categoria;
    this->_contador++;
    this->_id = _contador;
}

double Transacao::getValor() {
    return this->_valor;
}

std::string Transacao::getData() {
    return this->_data;
}

std::string Transacao::getDescricao() {
    return this->_descricao;
}

std::string Transacao::getCategoria() {
    return this->_categoria;
}

int Transacao::getID() {
    return this->_id;
}
