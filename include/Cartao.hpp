#ifndef CARTAO_H
#define CARTAO_H

#include "Despesa.hpp"

#include <string>
#include <list>
#include <memory>


class Cartao {
    private:
    int _contador_de_despesas = 0;
    std::string _nome;
    double _fatura;
    double _limite_cartao;
    std::string _fechamento;
    std::list<std::shared_ptr<Despesa>> _lista_de_despesas;

    public:
    Cartao(std::string nome, double limite_cartao, std::string fechamento);
    Cartao();
    std::string getNome();
    void setNome(std::string nome);
    void alterarLimiteCartao(double limite);
    void adicionarDespesa();
    void adicionarDespesa(Despesa &despesa);
    void removerDespesa();
    void ultimasDespesas();
};

#endif