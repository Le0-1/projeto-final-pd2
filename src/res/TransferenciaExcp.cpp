#include "TransferenciaExcp.hpp"

/*Métodos DataInvalida*/
trfexcp::DataInvalida::DataInvalida(std::string data) {
    this->_data = data;
}

const char* trfexcp::DataInvalida::what() const throw() {
    return "ERRO 🕵️: Data informada não está no formado dd-mm-aaaa ou é inválida";
}

std::string trfexcp::DataInvalida::getData() {
    return this->_data;
}

/*Métodos TransferenciaInválida*/
trfexcp::TransferenciaInvalida::TransferenciaInvalida(std::string nome) {
    this->_nome_da_conta = nome;
}

const char* trfexcp::TransferenciaInvalida::what() const throw() {
    return "ERRO 🕵️: Não pode realizar transferência para uma mesma conta";
}

std::string trfexcp::TransferenciaInvalida::getNomeConta() {
    return this->_nome_da_conta;
}
