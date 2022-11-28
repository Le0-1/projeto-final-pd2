#include "GerenciaContaExcp.hpp"

/*Métodos para SaldoInvalido*/

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

/*Métodos para ContaNaoEncontrada*/
gcexcp::ContaNaoEncontrada::ContaNaoEncontrada(std::string nome) {
    this->_nome = nome;
}

std::string gcexcp::ContaNaoEncontrada::getNome() {
    return this->_nome;
}

const char* gcexcp::ContaNaoEncontrada::what() const throw() {
    return "Conta não encontrada";
}
