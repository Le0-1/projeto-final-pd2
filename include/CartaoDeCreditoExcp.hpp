#ifndef CARTAO_DE_CREDITO_EXCP_H
#define CARTAO_DE_CREDITO_EXCP_H

#include <exception>
#include <string>

class LimiteExcedido : public std::exception {
    private:
        std::string _nome_cartao, _numero_cartao;
        double _limite_cartao;

    public:
        LimiteExcedido(std::string nome_cartao, std::string numero_cartao,
                       double limite_cartao);

        const char* what() const throw();

        std::string getNomeCartao();

        std::string getNumeroCartao();

        double getLimiteCartao();
};

#endif // !CARTAO_DE_CREDITO_EXCP_H
