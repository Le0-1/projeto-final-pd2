#ifndef DESPESA_H
#define DESPESA_H

#include "ContaBancaria.hpp"
#include "Transacao.hpp"

#include <memory>

class Despesa : Transacao {
    private:
        std::shared_ptr<ContaBancaria> _conta = nullptr;
        bool _despesa_cartao_credito;
    
    public:
        Despesa(double valor, std::string descricao, std::string data, std::string categoria, std::shared_ptr<ContaBancaria> conta, bool despesa_cartao_credito);

        //caso não seja informado se a despesa é do cartão, será false por default
        Despesa(double valor, std::string descricao, std::string data, std::string categoria, std::shared_ptr<ContaBancaria> conta);

        std::shared_ptr<ContaBancaria> getConta();
        void alterarConta(std::shared_ptr<ContaBancaria> novo_banco);

        bool isDespesaCartaoCredito();
        void setDespesaCartaoCredito(bool arg);

};

#endif

