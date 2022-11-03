#ifndef CONTABANCARIA_H
#define CONTABANCARIA_H

#include "Cartao.hpp"

#include <string>
#include <map>

class ContaBancaria {
    private:
    std::map<std::string, Cartao> _cartoes;

    public:
    ContaBancaria();
    void adicioanarCartao(Cartao cartao);
    void removerCartao(Cartao cartao);
    void imprimirCartoes();

};

#endif