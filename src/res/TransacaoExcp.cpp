#include "TransacaoExcp.hpp"

/*Métodos para TransacaoNaoEncontrada*/
trsexcp::TransacaoNaoEncontrada::TransacaoNaoEncontrada(int id) {
    this->_id = id;
}

const char* trsexcp::TransacaoNaoEncontrada::what() const throw() {
    return "Transação não encontrada";
}

int trsexcp::TransacaoNaoEncontrada::getID() {
    return this->_id;
}

// Metodo para TipoTransacaoInvalido
trsexcp::TipoTransacaoInvalido::TipoTransacaoInvalido(std::string tipo) {
    this->_tipo = tipo;
}

std::string trsexcp::TipoTransacaoInvalido::getTipo() {
    return this->_tipo;
}

const char* trsexcp::TipoTransacaoInvalido::what() const throw() {
    return "O tipo da transacao é inválida";
}
