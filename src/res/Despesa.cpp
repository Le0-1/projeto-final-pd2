#include "Despesa.hpp"

Despesa::Despesa(double valor, std::string descricao, std::string data,
    std::string categoria, std::string conta, bool despesa_cartao_credito) 
    : Transacao(valor, descricao, data, categoria), _conta(conta),
    _despesa_cartao_credito(despesa_cartao_credito) { }

Despesa::Despesa(double valor, std::string descricao, std::string data,
    std::string categoria, std::string conta) : Transacao(valor, descricao,
    data, categoria), _conta(conta), _despesa_cartao_credito(false) { }

std::string Despesa::getConta() {
    return this->_conta;
}

void Despesa::alterarConta(std::string nova_conta) {
    this->_conta = nova_conta;
}

bool Despesa::isDespesaCartaoCredito() {
    return this->_despesa_cartao_credito;
}

void Despesa::setDespesaCartaoCredito(bool arg) {
    this->_despesa_cartao_credito = arg;
}

