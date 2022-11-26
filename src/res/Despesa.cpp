#include "Despesa.hpp"

Despesa::Despesa(double valor, std::string data, std::string categoria,
                 std::string conta) : Transacao(valor, data, categoria) {
    this->_conta = conta;
}

std::string Despesa::getConta() {
    return this->_conta;
}

void Despesa::alterarConta(std::string nova_conta) {
    this->_conta = nova_conta;
}
