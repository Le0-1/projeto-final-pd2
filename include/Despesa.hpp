#ifndef DESPESA_H
#define DESPESA_H

#include "Transacao.hpp"

#include <memory>

class Despesa : Transacao {
    private:
        std::string _conta;
        bool _despesa_cartao_credito;
    
    public:
        Despesa(double valor, std::string descricao, std::string data,
            std::string categoria, std::string conta,
            bool despesa_cartao_credito);

        // caso não seja informado se a despesa é do cartão, será false por default
        Despesa(double valor, std::string descricao, std::string data,
            std::string categoria, std::string conta);

        std::string getConta();

        void alterarConta(std::string novo_banco);

        bool isDespesaCartaoCredito();

        void setDespesaCartaoCredito(bool arg);

};

#endif

