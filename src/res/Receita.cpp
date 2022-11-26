#include "Receita.hpp"

Receita::Receita(std::string conta, double valor, std::string descricao, 
    std::string data, std::string categoria) : Transacao(valor, descricao, data, 
        categoria){
    this->_conta = conta;
}

void Receita::alterarConta(std::string conta_destino) {
    this->_conta = conta_destino;
}

std::string Receita::getConta() {
    return this->_conta;
}