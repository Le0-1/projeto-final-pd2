#include "TransferenciaExcp.hpp"

/*Métodos TransferenciaInválida*/
trfexcp::TransferenciaInvalida::TransferenciaInvalida(std::string nome) {
    this->_nome_da_conta = nome;
}

const char* trfexcp::TransferenciaInvalida::what() const throw() {
    return "ERRO 🕵️: Não é possível realizar uma transferência para uma mesma conta";
}

std::string trfexcp::TransferenciaInvalida::getNomeConta() {
    return this->_nome_da_conta;
}
