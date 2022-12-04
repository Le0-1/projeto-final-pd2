#include "Despesa.hpp"

Despesa::Despesa(double valor, std::string data, std::string categoria,
        std::string conta) : Transacao(valor, data, categoria, "despesa") {
    this->_conta = conta;
}

std::string Despesa::getConta() {
    return this->_conta;
}

void Despesa::alterarConta(std::string nova_conta) {
    this->_conta = nova_conta;
}

void Despesa::imprimirInfo() {
    const std::string separador = "\t___________________________________";

    Utils::printColor(Foreground::f_red, separador);

    std::cout << "\tID: " << getID() << std::endl;

    if (getSubtipo() == "CarteiraBancaria") {
        std::cout << "\tCarteira Bancaria: " << getConta() << std::endl;
    }
    else if (getSubtipo() == "Carteira") {
        std::cout << "\tCarteira: " << getConta() << std::endl;
    }
    
    std::cout << "\tValor : ";

    std::string valor = std::to_string(getValor());
    valor  = "R$ " + valor.substr(0, valor.find(".") + 3);
    Utils::printColor(Foreground::f_red, valor);

    std::cout << "\tData: " << getData() << std::endl;
    std::cout << "\tCategoria: " << getCategoria() << std::endl;

    Utils::printColor(Foreground::f_red, separador);
}
