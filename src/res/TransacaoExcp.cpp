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

