#include "Receita.hpp"

Receita::Receita(ContaBancaria conta, double valor, std::string descricao, 
    std::string data, std::string categoria) : Transacao(valor, descricao, data, 
        categoria){
    this->_conta = conta;
}

void Receita::alterarConta(ContaBancaria conta_destino){
    this->_conta = conta_destino;
}

ContaBancaria Receita::getConta(){
    return this->_conta;
}