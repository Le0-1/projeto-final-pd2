#include "CartaoDeCredito.hpp"

CartaoDeCredito::CartaoDeCredito(std::string nome, std::string numero,
                                 std::string CVV, std::string fechamento,
                                 double limite_cartao) {
    this->_nome = nome;
    this->_numero = numero;
    this->_CVV = CVV;
    this->_fechamento = fechamento;
    this->_limite_cartao = limite_cartao;
}

std::string CartaoDeCredito::getNome() {
    return this->_nome;
}

std::string CartaoDeCredito::getNumero() {
    return this->_numero;
}

std::string CartaoDeCredito::getFechamento() {
    return this->_fechamento;
}

double CartaoDeCredito::getLimite() {
    return this->_limite_cartao;
}

std::list<std::shared_ptr<Despesa>>& CartaoDeCredito::getListaDeDespesas() {
    return this->_lista_de_despesas;
}

void CartaoDeCredito::alterarLimiteCartao(double novo_limite) {
    this->_limite_cartao = novo_limite;
}

void CartaoDeCredito::adicionarDespesa(double valor, std::string data,
                                       std::string categoria) {

    if (this->getTotalDespesas() + valor <= this->_limite_cartao) {
        // A "conta" de uma despesa do cartao de credito eh o nome do cartao
        this->_lista_de_despesas.push_back(std::shared_ptr<Despesa>
                (new Despesa(valor, data, categoria, this->_nome)));
    }
    else {
        throw LimiteExcedido(this->_nome, this->_numero, this->_limite_cartao);
    }
}

double CartaoDeCredito::getTotalDespesas() {
    double somaDespesas = 0;
    std::list<std::shared_ptr<Despesa>>::iterator it;
    for (it = this->_lista_de_despesas.begin(); it != this->_lista_de_despesas.end(); it++) {
        somaDespesas += (*it)->getValor();
    }
    return somaDespesas;
}

void CartaoDeCredito::listarDespesas() {
    std::cout << "--------------------" << std::endl;
    std::cout << "CARTAO: " << this->_nome << std::endl;
    std::cout << "NUMERO: " << this->_numero << std::endl;
    std::cout << "CVV: " << this->_CVV << std::endl;
    std::cout << "FECHAMENTO:" << this->_fechamento << std::endl;
    std::cout << "--------------------" << std::endl;

    std::list<std::shared_ptr<Despesa>>::iterator it;
    for (it = this->_lista_de_despesas.begin(); it != this->_lista_de_despesas.end(); it++) {
        std::cout << "ID: " << (*it)->getID() << std::endl;
        std::cout << "DATA: " << (*it)->getData() << std::endl;
        std::cout << "VALOR: R$ " << (*it)->getValor();
        std::cout << "CATEGORIA: " << (*it)->getCategoria();
        std::cout << "--------------------" << std::endl;
    }
    std::cout << "VALOR PROXIMA FATURA: R$ " << this->getTotalDespesas() << std::endl;
    std::cout << "DESPESAS REGISTRADAS: " << this->_lista_de_despesas.size() << std::endl;
}

bool CartaoDeCredito::removerDespesa(int id) {
    std::list<std::shared_ptr<Despesa>>::iterator it;
    for (it = this->_lista_de_despesas.begin(); it != this->_lista_de_despesas.end(); it++) {
        if ((*it)->getID() == id) {
            this->_lista_de_despesas.erase(it);
            return true;
        }
    }
    return false;
}
