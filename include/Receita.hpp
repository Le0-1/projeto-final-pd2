#ifndef RECEITA_H
#define RECEITA_H

#include "ContaBancaria.hpp"

class Receita : public Transacao{
    private:
    ContaBancaria _conta;

    public:
    Receita(ContaBancaria conta, double valor, std::string descricao, 
        std::string data, std::string categoria);

    void alterarConta(ContaBancaria conta_destino);

    ContaBancaria getConta();

};

#endif