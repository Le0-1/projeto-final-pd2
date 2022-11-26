#include "Transferencia.hpp"
#include "Transacao.hpp"

Transferencia::Transferencia(double valor, std::string descricao, std::string data,
        std::string categoria, std::string origem, std::string destino)
        : Transacao(valor, descricao, data, categoria) {

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
