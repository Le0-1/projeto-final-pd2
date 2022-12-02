#include "GerenciaContaExcp.hpp"

/*Métodos para ValorInvalido*/

gcexcp::ValorInvalido::ValorInvalido(double valor, std::string nome) {
    this->_valor = valor;
    this->_nome = nome;
}

std::string  gcexcp::ValorInvalido::getNome() {
    return this->_nome;
}

double gcexcp::ValorInvalido::getValor() {
    return this->_valor;
}

const char* gcexcp::ValorInvalido::what() const throw() {
    return "Valor Invalido";
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

/*Métodos para PerfilVazio*/
gcexcp::PerfilVazio::PerfilVazio() {}

const char* gcexcp::PerfilVazio::what() const throw() {
    return "Não existem contas cadastradas nesse perfil";
}

// Metodos para ContaJaExiste

gcexcp::ContaJaExiste::ContaJaExiste(std::string nome) {
    this->_nome = nome;
}

const char* gcexcp::ContaJaExiste::what() const throw() {
    return "Já existem contas cadastradas com esse nome";
}

std::string gcexcp::ContaJaExiste::getNome() {
    return this->_nome;
}

// Metodos para ContaNaoPermiteCartao

gcexcp::ContaNaoPermiteCartao::ContaNaoPermiteCartao(std::string nome, std::string subtipo) {
    this->_nome_conta = nome;
    this->_subtipo_conta = subtipo;
}

const char* gcexcp::ContaNaoPermiteCartao::what() const throw() {
    return "A conta selecionada nao permite cartao de credito";
}

std::string gcexcp::ContaNaoPermiteCartao::getNomeConta() {
    return this->_nome_conta;
}

std::string gcexcp::ContaNaoPermiteCartao::getSubtipoConta() {
    return this->_subtipo_conta;
}

// Metodos para SaldoInsuficiente
gcexcp::SaldoInsuficiente::SaldoInsuficiente(double saldo, double despesa) {
    this->_saldo = saldo;
    this->_despesa = despesa;
}

const char * gcexcp::SaldoInsuficiente::what() const throw() {
    return "Saldo insuficiente";
}

double gcexcp::SaldoInsuficiente::getSaldo() {
    return this->_saldo;
}

double gcexcp::SaldoInsuficiente::getDespesa() {
    return this->_despesa;
}