#include "GerenciaContaExcp.hpp"

gcexcp::SaldoInvalido::SaldoInvalido(double saldo_inicial, std::string nome) {
    this->_saldo_inicial = saldo_inicial;
    this->_nome = nome;
}

std::string  gcexcp::SaldoInvalido::getNome() {
    return this->_nome;
}

double gcexcp::SaldoInvalido::getSaldoInicial() {
    return this->_saldo_inicial;
}

const char* gcexcp::SaldoInvalido::what() const throw() {
    return "Saldo Invalido";
}