#include "GerenciaConta.hpp"
#include "GerenciaContaExcp.hpp"
#include "CarteiraExcp.hpp"
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
        throw ctrexcp::ContaNaoEncontrada(nome);
    }

    else {
        return getContas().find(nome)->second;
    }
}

void GerenciaConta::adicionarCarteira(std::string nome, double saldo_inicial) {

    if (getContas().find(nome) == getContas().end()) {
        std::shared_ptr<Carteira> carteira = std::make_shared<Carteira>(nome, saldo_inicial);
        this->_contas.insert(std::pair<std::string, std::shared_ptr<Carteira>>(nome, carteira));
    }

    else {
        throw ctrexcp::ContaJaExiste(nome);
    }
}

void GerenciaConta::adicionarConta(std::string nome, double saldo_inicial) {
    if (getContas().find(nome) == getContas().end()) {
        std::shared_ptr<ContaBancaria> conta = std::make_shared<ContaBancaria>(nome, saldo_inicial);
        this->_contas.insert(std::pair<std::string, std::shared_ptr<Carteira>>(nome, conta));
    }
    else {
        throw ctrexcp::ContaJaExiste(nome);
    }
}

void GerenciaConta::removerConta(std::string nome) {

    /*A funcao 'find' de um map retorna um ponteiro para map.end se nao encontrar nada*/
    if (this->getContas().find(nome) == this->getContas().end()) {
        throw ctrexcp::ContaNaoEncontrada(nome);
    }

    this->_contas.erase(this->_contas.find(nome));
}

void GerenciaConta::adicionarReceita(std::string conta, double valor, std::string data, std::string categoria) {
    
    std::shared_ptr<Receita> receita = std::make_shared<Receita>(conta, valor, data, categoria);
    getConta(conta)->adicionarTransacao(receita);
}

void GerenciaConta::adicionarDespesa(std::string conta, double valor, std::string data, std::string categoria) {
    std::shared_ptr<Despesa> despesa = std::make_shared<Despesa>(valor, data, categoria, conta);
    getConta(conta)->adicionarTransacao(despesa);
}

void GerenciaConta::adicionarDespesaCartao(std::string conta, std::string cartao, double valor, std::string data, std::string categoria) {

    if (getConta(conta)->getSubtipo() == "ContaBancaria") {
        std::shared_ptr<ContaBancaria> conta_bancaria;
        conta_bancaria = std::dynamic_pointer_cast<ContaBancaria>(getConta(conta));
        conta_bancaria->getCartaoDeCredito(cartao)->adicionarDespesa(valor, data, categoria);
    }
    else {
        throw ctrexcp::ContaNaoPermiteCartao(conta, getConta(conta)->getSubtipo());
    }
}

void GerenciaConta::adicionarTransferencia(double valor, std::string data, std::string categoria,   
                                           std::string origem, std::string destino) {

    //regex mais simples = ^([0-2][0-9]|(3)[0-1])(\\/)(((0)[0-9])|((1)[0-2]))(\\/)\\d{4}$

    const std::string valid_date = "^(?:(?:31(\\/|-|\\.)(?:0?[13578]|1[02]))\\1|(?:(?:29|30)"
                                  "(\\/|-|\\.)(?:0?[13-9]|1[0-2])\\2))(?:(?:1[6-9]|[2-9]\\d)"
                                  "?\\d{2})$|^(?:29(\\/|-|\\.)0?2\\3(?:(?:(?:1[6-9]|[2-9]\\d)?"
                                  "(?:0[48]|[2468][048]|[13579][26])|(?:(?:16|[2468][048]|"
                                  "[3579][26])00))))$|^(?:0?[1-9]|1\\d|2[0-8])(\\/|-|\\.)"
                                  "(?:(?:0?[1-9])|(?:1[0-2]))\\4(?:(?:1[6-9]|[2-9]\\d)?\\d{2})$";


    if (origem == destino) {
        throw trfexcp::TransferenciaInvalida(origem);
    }

    else if (std::regex_match(data, std::regex(valid_date))) {

        std::shared_ptr<Transferencia> transferencia = std::make_shared<Transferencia>
                                                   (valor, data, categoria, origem, destino);

        getTransferencias().insert(std::pair<int, std::shared_ptr<Transferencia>>
                                                   (transferencia->getID(), transferencia));

        double saldo_conta_origem = getConta(origem)->getSaldoAtual();
        double saldo_conta_destino = getConta(destino)->getSaldoAtual();

        getConta(origem)->setSaldoAtual(saldo_conta_origem - valor);
        getConta(destino)->setSaldoAtual(saldo_conta_destino + valor);

    } 
    else {
        throw trfexcp::DataInvalida(data);
    }
}

void GerenciaConta::removerReceita(std::string conta, int id) {

    if (getConta(conta)->getTransacoes().find(id) == getConta(conta)->getTransacoes().end()) {
        throw trsexcp::TransacaoNaoEncontrada(id);       
    }

    else if (getConta(conta)->getTransacoes().find(id)->second->getSubtipo() == "despesa") {
        throw trsexcp::TipoTransacaoInvalido("despesa");
    }
 
    else {
        getConta(conta)->removerTransacao(id);
    }
}

void GerenciaConta::removerDespesa(std::string conta, int id) {

    if (getConta(conta)->getTransacoes().find(id) == getConta(conta)->getTransacoes().end()) {
        throw trsexcp::TransacaoNaoEncontrada(id);       
    }

    else if (getConta(conta)->getTransacoes().find(id)->second->getSubtipo() == "receita") {
        throw trsexcp::TipoTransacaoInvalido("receita");
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
        throw ctrexcp::SaldoInsuficiente(conta_destino->getSaldoAtual(), tr->getValor());
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
                if(std::regex_match(fechamento, std::regex("^(([0]?[1-9])|([1-2][0-9])|"
                                                           "(3[01]))$"))) {

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
        throw ctrexcp::ContaNaoPermiteCartao(conta, getConta(conta)->getSubtipo());
    }
}

void GerenciaConta::removerCartao(std::string conta, std::string cartao) {

    if (getConta(conta)->getSubtipo() == "ContaBancaria") {
        std::shared_ptr<ContaBancaria> conta_bancaria;
        conta_bancaria = std::dynamic_pointer_cast<ContaBancaria>(getConta(conta));

        conta_bancaria->removerCartao(cartao);
    }
    else {
        throw ctrexcp::ContaNaoPermiteCartao(conta, getConta(conta)->getSubtipo());
    }
}

void GerenciaConta::pagarFatura(std::string conta, std::string cartao) {

    if (getConta(conta)->getSubtipo() == "ContaBancaria") {
        std::shared_ptr<ContaBancaria> conta_bancaria;
        conta_bancaria = std::dynamic_pointer_cast<ContaBancaria>(getConta(conta));

        conta_bancaria->pagarFatura(cartao);
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

        std::cout << "Conta: " << cart_conta->getNome() << std::endl;

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
