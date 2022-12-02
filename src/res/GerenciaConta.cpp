#include "GerenciaConta.hpp"
#include "GerenciaContaExcp.hpp"
#include "TransacaoExcp.hpp"
#include <algorithm>
#include <cctype>
#include <memory>

GerenciaConta::GerenciaConta() { }

std::map<std::string, std::shared_ptr<Carteira>>& GerenciaConta::getContas() {
    return this->_contas;
}

std::map<int, std::shared_ptr<Transferencia>>& GerenciaConta::getTransferencias() {
    return this->_transferencias;
}

std::shared_ptr<Carteira> GerenciaConta::getConta(std::string nome) {
    if (getContas().find(nome) == getContas().end()) {
        throw gcexcp::ContaNaoEncontrada(nome);
    }

    else {
        return getContas().find(nome)->second;
    }
}

void GerenciaConta::adicionarCarteira(std::string nome, double saldo_inicial) {
    if (saldo_inicial < 0) {
        throw gcexcp::ValorInvalido(saldo_inicial, nome);
    }

    if (getContas().find(nome) == getContas().end()) {
        std::shared_ptr<Carteira> carteira = std::make_shared<Carteira>(nome, saldo_inicial);
        getContas().insert(std::pair<std::string, std::shared_ptr<Carteira>>(nome, carteira));
    }
    else {
        throw gcexcp::ContaJaExiste(nome);
    }
}

void GerenciaConta::adicionarConta(std::string nome, double saldo_inicial) {
    if (saldo_inicial < 0) {
        throw gcexcp::ValorInvalido(saldo_inicial, nome);
    }

    if (getContas().find(nome) == getContas().end()) {
        std::shared_ptr<ContaBancaria> conta = std::make_shared<ContaBancaria>(nome, saldo_inicial);
        getContas().insert(std::pair<std::string, std::shared_ptr<Carteira>>(nome, conta));
    }
    else {
        throw gcexcp::ContaJaExiste(nome);
    }
}

void GerenciaConta::removerConta(std::string nome) {

    /*A funcao 'find' de um map retorna um ponteiro para map.end se nao encontrar nada*/
    if (this->getContas().find(nome) == this->getContas().end()) {
        throw gcexcp::ContaNaoEncontrada(nome);
    }

    getContas().erase(getContas().find(nome));
}

void GerenciaConta::adicionarReceita(std::string conta, double valor, std::string data, std::string categoria) {
    if (this->getContas().find(conta) == this->getContas().end()) {
        throw gcexcp::ContaNaoEncontrada(conta);
    }
    if (valor < 0) throw gcexcp::ValorInvalido(valor, conta);

    std::shared_ptr<Receita> receita = std::make_shared<Receita>(conta, valor, data, categoria);
    getConta(conta)->adicionarTransacao(receita);
}

void GerenciaConta::adicionarDespesa(std::string conta, double valor, std::string data, std::string categoria) {
    if(valor <= getConta(conta)->getSaldoAtual()) {
        std::shared_ptr<Despesa> despesa = std::make_shared<Despesa>(valor, data, categoria, conta);
        getConta(conta)->adicionarTransacao(despesa);
    } 
    else {
        throw gcexcp::SaldoInsuficiente(getConta(conta)->getSaldoAtual(), valor);
    }
}

void GerenciaConta::adicionarDespesaCartao(std::string conta, std::string cartao, double valor, std::string data, std::string categoria) {

    if (getConta(conta)->getSubtipo() == "ContaBancaria") {
        std::shared_ptr<ContaBancaria> conta_bancaria;
        conta_bancaria = std::dynamic_pointer_cast<ContaBancaria>(getConta(conta));
        conta_bancaria->getCartaoDeCredito(cartao).adicionarDespesa(valor, data, categoria);
    }
    else {
        throw gcexcp::ContaNaoPermiteCartao(conta, getConta(conta)->getSubtipo());
    }
}

void GerenciaConta::adicionarTransferencia(double valor, std::string data, std::string categoria,   
                                           std::string origem, std::string destino) {

    std::string valid_date = "^([0-2][0-9]|(3)[0-1])(\\/)(((0)[0-9])|((1)[0-2]))(\\/)\\d{4}$";

    if (std::regex_match(data, std::regex(valid_date))) {

        std::shared_ptr<Transferencia> transferencia = std::make_shared<Transferencia>
                                                   (valor, data, categoria, origem, destino);

        getTransferencias().insert(std::pair<int, std::shared_ptr<Transferencia>>
                                                   (transferencia->getID(), transferencia));

        double saldo_conta_origem = getConta(origem)->getSaldoAtual();
        double saldo_conta_destino = getConta(destino)->getSaldoAtual();

        getConta(origem)->setSaldoAtual(saldo_conta_origem - valor);
        getConta(destino)->setSaldoAtual(saldo_conta_destino + valor);

    } else {
        throw trfexcp::DataInvalida(data);
    }
}

void GerenciaConta::removerReceita(std::string conta, int id) {

    if (getConta(conta)->getTransacoes().find(id) == getConta(conta)->getTransacoes().end()) {
        throw trsexcp::TransacaoNaoEncontrada(id);       
    } 
    else {
        getConta(conta)->removerTransacao(id);
    }
}

void GerenciaConta::removerDespesa(std::string conta, int id) {

    if (getConta(conta)->getTransacoes().find(id) == getConta(conta)->getTransacoes().end()) {
        throw trsexcp::TransacaoNaoEncontrada(id);
    } 
    else {
        getConta(conta)->removerTransacao(id);
    }
}

void GerenciaConta::removerDespesaCartao(std::string conta, std::string cartao, int id) {

    if (getConta(conta)->getSubtipo() == "ContaBancaria") {
        std::shared_ptr<ContaBancaria> conta_bancaria;
        conta_bancaria = std::dynamic_pointer_cast<ContaBancaria>(getConta(conta));
        conta_bancaria->getCartoes().find(cartao)->second.removerDespesa(id);
    }
}

void GerenciaConta::removerTransferencia(int id) {
    if (this->_transferencias.find(id) == this->_transferencias.end()) {
        throw trsexcp::TransacaoNaoEncontrada(id);
    }

    std::shared_ptr<Transferencia> tr = this->_transferencias.find(id)->second;
    std::shared_ptr<Carteira> conta_origem = this->getConta(tr->getOrigem());
    std::shared_ptr<Carteira> conta_destino = this->getConta(tr->getDestino());
    
    // Eh necessario verificar se ha saldo suficiente na conta de destino,
    // caso contrario a conta poderia ficar com saldo negativo
    if (conta_destino->getSaldoAtual() < tr->getValor()) {
        throw gcexcp::SaldoInsuficiente(conta_destino->getSaldoAtual(), tr->getValor());
    }

    conta_origem->setSaldoAtual(conta_origem->getSaldoAtual() + tr->getValor());
    conta_destino->setSaldoAtual(conta_origem->getSaldoAtual() - tr->getValor());

    getTransferencias().erase(getTransferencias().find(id));
}

void GerenciaConta::adicionarCartao(std::string conta, std::string nome,
                                    std::string numero, std::string CVV,
                                    std::string fechamento, double limite_cartao) {

    if (getConta(conta)->getSubtipo() == "ContaBancaria") {

        if (std::regex_match(numero, std::regex("^[0-9]{16}$"))) {
            if (std::regex_match(CVV, std::regex("^[0-9]{3}$"))) {
                if(std::regex_match(fechamento, std::regex("^([1-9]|[12][0-9]|3[01])$"))) {

                    std::shared_ptr<ContaBancaria> conta_bancaria;
                    conta_bancaria = std::dynamic_pointer_cast<ContaBancaria>(getConta(conta));

                    CartaoDeCredito cartao_de_credito(nome, numero, CVV, fechamento, limite_cartao);
                    conta_bancaria->adicionarCartao(cartao_de_credito);

                } else {
                    throw cdcexcp::FechamentoInvalido(fechamento);
                }
            } else {
                throw cdcexcp::CVVInvalido(CVV);
            }
        } else {
            throw cdcexcp::NumeroInvalido(numero);
        }

    } else {
        throw gcexcp::ContaNaoPermiteCartao(conta, getConta(conta)->getSubtipo());
    }
}

void GerenciaConta::removerCartao(std::string conta, std::string cartao) {

    if (getConta(conta)->getSubtipo() == "ContaBancaria") {
        std::shared_ptr<ContaBancaria> conta_bancaria;
        conta_bancaria = std::dynamic_pointer_cast<ContaBancaria>(getConta(conta));

        conta_bancaria->removerCartao(cartao);
    }
    else {
        throw gcexcp::ContaNaoPermiteCartao(conta, getConta(conta)->getSubtipo());
    }
}

void GerenciaConta::pagarFatura(std::string conta, std::string cartao) {

    if (getConta(conta)->getSubtipo() == "ContaBancaria") {
        std::shared_ptr<ContaBancaria> conta_bancaria;
        conta_bancaria = std::dynamic_pointer_cast<ContaBancaria>(getConta(conta));

        CartaoDeCredito cartao_de_credito = conta_bancaria->getCartaoDeCredito(cartao);

        std::list<std::shared_ptr<Despesa>> lista_despesas;
        lista_despesas = cartao_de_credito.getListaDespesas();

        for (std::shared_ptr<Despesa> despesa : lista_despesas) {
            adicionarDespesa(conta, despesa->getValor(), despesa->getData(),
                             despesa->getCategoria());
        }
        lista_despesas.clear();
    }
}

void GerenciaConta::imprimirContas() {
    if(!(_contas.empty())) {
        for (auto const& conta : getContas()) {
            conta.second->imprimirInfo();
        }
    } 
    else {
        throw gcexcp::PerfilVazio();
    }
}

void GerenciaConta::listarTransacao(std::string conta, std::string tipo) {
    std::transform(tipo.begin(), tipo.end(), tipo.begin(), ::tolower);
    if (tipo == "despesa" or tipo == "receita") {
        std::shared_ptr<Carteira> cart_conta = getConta(conta);

        std::cout << "ContaBancaria: " << cart_conta->getNome() << std::endl;

        int i = 0;
        for (auto const&it : getConta(conta)->getTransacoes()) {
            if (it.second->getSubtipo() == tipo) {
                std::cout << std::endl; 
                it.second->imprimirInfo();
                ++i;
            }   
        }

        if (i == 0) {
            std::cout << std::endl;
            Utils::printColor(Efeitos::inverse, "nenhuma " + tipo + " encontrada");
        }
    }
    else {
        throw trsexcp::TipoTransacaoInvalido(tipo);
    }
}
