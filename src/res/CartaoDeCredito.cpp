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

std::list<std::shared_ptr<Despesa>>& CartaoDeCredito::getListaDespesas() {
    return this->_lista_despesas;
}

void CartaoDeCredito::alterarLimiteCartao(double novo_limite) {
    this->_limite_cartao = novo_limite;
}

void CartaoDeCredito::adicionarDespesa(double valor, std::string data,
                                       std::string categoria) {

    if (this->getTotalDespesas() + valor <= this->_limite_cartao) {
        // A "conta" de uma despesa do cartao de credito eh o nome do cartao
        _lista_despesas.emplace_back(std::make_shared<Despesa>(valor, data, categoria, _nome));
    } else {
        throw LimiteExcedido(_nome, _numero, _limite_cartao);
    }
}

double CartaoDeCredito::getTotalDespesas() {
    double soma_despesas = 0;
    for (auto const& despesa : _lista_despesas) {
        soma_despesas += despesa->getValor();
    }
    return soma_despesas;
}

void CartaoDeCredito::listarDespesas() {
    std::cout << "--------------------"
              << "\nCARTAO: " << this->_nome
              << "\nNUMERO: " << this->_numero
              << "\nCVV: " << this->_CVV
              << "\nFECHAMENTO:" << this->_fechamento
              << "\n--------------------" << std::endl;

    for (auto const& despesa : _lista_despesas) {
        std::cout << "ID: " << despesa->getID()
                  << "\nDATA: " << despesa->getData()
                  << "\nVALOR: R$ " << despesa->getValor()
                  << "\nCATEGORIA: " << despesa->getCategoria()
                  << "\n--------------------" << std::endl;
    }

    std::cout << "VALOR PROXIMA FATURA: R$ " << this->getTotalDespesas() << std::endl;
    std::cout << "DESPESAS REGISTRADAS: " << this->_lista_despesas.size() << std::endl;
}

bool CartaoDeCredito::removerDespesa(int id) {
    std::list<std::shared_ptr<Despesa>>::iterator it;
    for (it = this->_lista_despesas.begin(); it != this->_lista_despesas.end(); it++) {
        if ((*it)->getID() == id) {
            this->_lista_despesas.erase(it);
            return true;
        }
    }
    return false;
}
