#include "Cartao.hpp"

#include <memory>
#include <iostream>
#include <algorithm>

Cartao::Cartao() {
    this->_limite_cartao = 0;
    this->_nome = "Ainda nao foi dado um nome";
    this->_fechamento = "Ainda nao foi dado um dia de fechamento";
}

Cartao::Cartao(std::string nome, double limite_cartao, std::string fechamento) {
    this->_nome = nome;
    this->_limite_cartao = limite_cartao;
    this->_fechamento = fechamento;
}

std::string Cartao::getNome() {
    return this->_nome;
}

void Cartao::setNome(std::string nome) {
    this->_nome = nome;
}

void Cartao::alterarLimiteCartao(double limite) {
    this->_limite_cartao = limite;
}

void Cartao::adicionarDespesa() {
    std::cout << "===== DENTRO DE ADICIONAR DESPESA =====" << std::endl;
    std::cout << "Digite o valor da despesa: " << std::endl;
    double valor;
    std::cin >> valor;

    std::cin.ignore();
    std::cout << "Digite a descrição da despesa: " << std::endl;
    std::string descricao;
    std::getline(std::cin, descricao);

    std::unique_ptr<Despesa> nova_despesa(new Despesa(valor, descricao));
    this->_contador_de_despesas++;
    nova_despesa->setId(this->_contador_de_despesas);

    this->_lista_de_despesas.push_back(move(nova_despesa));
    std::cout << "-------------------------------------" << std::endl; 
}

void Cartao::removerDespesa() {
    std::cout << "===== DENTRO DE REMOVER DESPESA =====" << std::endl;
    std::cout << std::endl;
    if(this->_lista_de_despesas.size() == 0) {
        std::cout << "Você não tem despesas! " << std::endl;
        return; 
    }

    std::cout << "Veja o ID para remover a despesa: " << std::endl;
    std::cout << std::endl;
    this->ultimasDespesas();
    int id;
    std::cout << "Digite a id da despesa" << std::endl;
    std::cin >> id;

    std::list<std::shared_ptr<Despesa>>::iterator it;
    for(it = this->_lista_de_despesas.begin(); it != this->_lista_de_despesas.end(); it++) {
        
        if( (*it)->getId() == id ) {
           this->_lista_de_despesas.erase(it);
           this->_contador_de_despesas--;
        }
        else if( it == this->_lista_de_despesas.end() ) {
            std::cout << "O ID da despesa não foi encontrado" << std::endl;
        }
        break;
    }
    std::cout << "-------------------------------------" << std::endl;
}

void Cartao::ultimasDespesas() {
    if(this->_lista_de_despesas.size() == 0) {
        std::cout << "Voce não tem despesas!" << std::endl;
        return;
    }

    std::cout << "Ùltimas Despesas: " << std::endl;

    std::list<std::shared_ptr<Despesa>>::iterator it;
    for(it = this->_lista_de_despesas.begin(); it != this->_lista_de_despesas.end(); ++it) {

        std::cout << "ID da despesa: " << (*it)->getId() << "\t";
        std::cout << "\t Descrição: "<<(*it)->getDescricao() << "\t";
        std::cout << "\t Valor:" <<(*it)->getValor();
        std::cout << std::endl;
    }
    std::cout << "-------------------------------------" << std::endl;
}
