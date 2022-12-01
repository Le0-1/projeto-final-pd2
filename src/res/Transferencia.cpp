#include "Transferencia.hpp"
#include "Transacao.hpp"

Transferencia::Transferencia(double valor, std::string data,
        std::string categoria, std::string origem, std::string destino)
        : Transacao(valor, data, categoria, "transferencia") {

    this->_origem = origem;
    this->_destino = destino;
}

void Transferencia::alterarDestino(std::string novo_destino) {
    this->_destino = novo_destino;
}

void Transferencia::alterarOrigem(std::string nova_origem) {
    this->_origem = nova_origem;
}

std::string Transferencia::getOrigem() {
    return this->_origem;
}

std::string Transferencia::getDestino() {
    return this->_destino;
}

void Transferencia::imprimirInfo() {
    const std::string separador = "\t___________________________________";

    Utils::printColor(Foreground::f_yellow, separador);

    std::cout << "\tID: " << getID() << std::endl;
    std::cout << "\tOrigem: " << getOrigem() << std::endl;
    std::cout << "\tDestino: " << getDestino() << std::endl;
    std::cout << "\tValor : ";

    std::string valor = std::to_string(getValor());
    valor  = "R$ " + valor.substr(0, valor.find(".") + 3);
    Utils::printColor(Foreground::f_green, valor);

    std::cout << "\tData: " << getData() << std::endl;
    std::cout << "\tCategoria: " << getCategoria() << std::endl;

    Utils::printColor(Foreground::f_yellow, separador);
}
