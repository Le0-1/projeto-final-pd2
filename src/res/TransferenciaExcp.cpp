#include "TransferenciaExcp.hpp"

trfexcp::DataInvalida::DataInvalida(std::string data) {
    this->_data = data;
}

const char* trfexcp::DataInvalida::what() const throw() {
    return "Data informada não está no formado dd/mm/aaaa ou é inválida";
}

std::string trfexcp::DataInvalida::getData() {
    return this->_data;
}