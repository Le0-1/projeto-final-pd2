#include "CartaoDeCredito.hpp"

CartaoDeCredito::CartaoDeCredito(std::string nome, std::string numero,
                                 std::string CVV, std::string fechamento,
                                 double limite_cartao) {
    this->_nome = nome;
    this->_numero = numero;
    this->_CVV = CVV;
    this->_fechamento = fechamento;

    if (limite_cartao < 0) {
        throw LimiteInvalido(nome, numero, limite_cartao);
    }

    this->_limite_cartao = limite_cartao;
}

std::string CartaoDeCredito::getNome() {
    return this->_nome;
}

std::string CartaoDeCredito::getNumero() {
    return this->_numero;
}

std::string CartaoDeCredito::getCVV() {
    return this->_CVV;
}

std::string CartaoDeCredito::getFechamento() {
    return this->_fechamento;
}

double CartaoDeCredito::getLimite() {
    return this->_limite_cartao;
}

std::list<std::shared_ptr<Despesa>>& CartaoDeCredito::getListaDespesas() {
    return this->_despesas;
}

void CartaoDeCredito::alterarLimiteCartao(double novo_limite) {
    if (novo_limite < 0) {
        throw LimiteInvalido(this->_nome, this->_numero, novo_limite);
    }

    this->_limite_cartao = novo_limite;
}

void CartaoDeCredito::adicionarDespesa(double valor, std::string data,
                                       std::string categoria) {

    if (this->getTotalDespesas() + valor <= this->_limite_cartao) {
        // A "conta" de uma despesa do cartao de credito eh o nome do cartao
        _despesas.emplace_back(std::make_shared<Despesa>(valor, data, categoria, _nome));
    } else {
        throw LimiteExcedido(_nome, _numero, _limite_cartao);
    }
}

double CartaoDeCredito::getTotalDespesas() {
    double soma_despesas = 0;
    for (auto const& despesa : _despesas) {
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

    for (auto const& despesa : _despesas) {
        std::cout << "ID: " << despesa->getID()
                  << "\nDATA: " << despesa->getData()
                  << "\nVALOR: R$ " << despesa->getValor()
                  << "\nCATEGORIA: " << despesa->getCategoria()
                  << "\n--------------------" << std::endl;
    }

    std::cout << "VALOR PROXIMA FATURA: R$ " << this->getTotalDespesas() << std::endl;
    std::cout << "DESPESAS REGISTRADAS: " << this->_despesas.size() << std::endl;
}

bool CartaoDeCredito::removerDespesa(int id) {
    std::list<std::shared_ptr<Despesa>>::iterator it;
    for (it = this->_despesas.begin(); it != this->_despesas.end(); it++) {
        if ((*it)->getID() == id) {
            this->_despesas.erase(it);
            return true;
        }
    }
    return false;
}

void CartaoDeCredito::imprimirInfo() {
    const std::string separador = "\t___________________________________";
    Utils::printColor(Foreground::f_cyan, separador);

    std::cout << "\tCartao de credito: " << getNome() << std::endl;
    std::cout << "\tNumero " << getNumero() << ", CVV " << getCVV() << std::endl;
    std::cout << "\tFechamento: " << getFechamento() << std::endl;
    std::cout << "\tLimite total: R$ " << std::fixed << std::setprecision(2) << getLimite() << std::endl;
    std::cout << "\tLimite disponivel: ";

    double limite_disp_t = getLimite() - getTotalDespesas();
    std::string limite_disp = std::to_string(limite_disp_t);
    limite_disp = "R$ " + limite_disp.substr(0, limite_disp.find(".") + 3);

    if (limite_disp_t > 0) {
        Utils::printColor(Foreground::f_green, limite_disp);
    } 
    else if (limite_disp_t <= 0) {
        Utils::printColor(Foreground::f_red, limite_disp);
    }

    std::cout << "\tQuantidade de despesas: " << getListaDespesas().size() << std::endl;

    Utils::printColor(Foreground::f_cyan, separador);
}
