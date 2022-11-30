#include "TransacaoExcp.hpp"

/*Métodos para TransacaoNaoEncontrada*/
trexcp::TransacaoNaoEncontrada::TransacaoNaoEncontrada(int id) {
    this->_id = id;
}

const char* trexcp::TransacaoNaoEncontrada::what() const throw() {
    return "Transação não encontrada";
}

int trexcp::TransacaoNaoEncontrada::getID() {
    return this->_id;
}

