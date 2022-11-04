#include "Transacao.hpp"

int Transacao::contador = 0;

Transacao::Transacao(double valor, std::string descricao, std::string data, std::string categoria) {
    this->_valor = valor;
    this->_descricao = descricao;
    this->_data = data;
    this->_categoria = categoria;
    this->contador++;
    this->_id = contador;
}

double Transacao::GetValor() {
    return this->_valor;
}

std::string Transacao::GetDescricao() {
    return this->_descricao;
}

std::string Transacao::GetCategoria() {
    return this->_categoria;
}

int Transacao::GetID() {
    return this->_id;
}
