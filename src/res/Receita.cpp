#include "Receita.hpp"

Receita::Receita(std::string conta, double valor, std::string data,
        std::string categoria) : Transacao(valor, data, categoria, "receita") {
    this->_conta = conta;
}

void Receita::alterarConta(std::string conta_destino) {
    this->_conta = conta_destino;
}

std::string Receita::getConta() {
    return this->_conta;
}

void Receita::imprimirInfo() {
    const std::string separador = "\t___________________________________";

    Utils::printColor(Foreground::f_green, separador);

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
    Utils::printColor(Foreground::f_green, valor);

    std::cout << "\tData: " << getData() << std::endl;
    std::cout << "\tCategoria: " << getCategoria() << std::endl;

    Utils::printColor(Foreground::f_green, separador);
}
