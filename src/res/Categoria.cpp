#include "Categoria.hpp"

Categoria::Categoria(std::string categoria, std::string sub_categoria, int prioridade) : _categoria(categoria), _sub_categoria(sub_categoria), _prioridade(prioridade) {}

Categoria::Categoria(std::string categoria, std::string sub_categoria) : _categoria(categoria), _sub_categoria(sub_categoria) {
    definirPrioriadeDefault(categoria);
}

Categoria::Categoria(std::string categoria) {
    definirPrioriadeDefault(categoria);
}

void Categoria::definirPrioriadeDefault(std::string categoria) { 
    std::transform(categoria.begin(), categoria.end(), categoria.begin(), ::tolower);

    if(categoria == "moradia") {
        this->_prioridade = ALTA;
    } else if(categoria == "saude") {
        this->_prioridade = ALTA;
    } else if(categoria == "transporte") {
        this->_prioridade = MEDIA;
    } else if(categoria == "supermercado") {
        this->_prioridade = MEDIA;
    } else if(categoria == "moradia") {
        this->_prioridade = MEDIA;
    } else if(categoria == "restaurante") {
        this->_prioridade = BAIXA;
    } else if(categoria == "moradia") {
        this->_prioridade = BAIXA;
    } else {
        this->_prioridade = BAIXA;
    }      
}

std::string Categoria::getCategoria() {
    return this->_categoria;
}

std::string Categoria::getSubCategoria() {
    return this->_categoria;
}

void Categoria::setCategoria(std::string categoria) {
    this->_categoria = categoria;
}

void Categoria::setSubCategoria(std::string sub_categoria) {
    this->_sub_categoria = sub_categoria;
}

void Categoria::setPrioridade(int prioridade) {
    this->_prioridade = prioridade;
}