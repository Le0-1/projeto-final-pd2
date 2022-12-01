#include "GerenciaConta.hpp"

GerenciaConta::GerenciaConta() { }

std::map<std::string, std::shared_ptr<Carteira>>& GerenciaConta::getContas() {
    return this->_contas;
}

std::map<int, std::shared_ptr<Transferencia>>& GerenciaConta::getTransferencias() {
    return this->_transferencias;
}

std::shared_ptr<Carteira> GerenciaConta::getConta(std::string nome) {
    return getContas().find(nome)->second;
}

void GerenciaConta::adicionarCarteira(std::string nome, double saldo_inicial) {
    if (saldo_inicial < 0) {
        throw gcexcp::SaldoInvalido(saldo_inicial, nome);
    }

    std::shared_ptr<Carteira> carteira = std::make_shared<Carteira>(nome, saldo_inicial);
    getContas().insert(std::pair<std::string, std::shared_ptr<Carteira>>(nome, carteira));
}

void GerenciaConta::adicionarConta(std::string nome, double saldo_inicial) {
    if (saldo_inicial < 0) {
        throw gcexcp::SaldoInvalido(saldo_inicial, nome);
    }

    std::shared_ptr<ContaBancaria> conta = std::make_shared<ContaBancaria>(nome, saldo_inicial);
    getContas().insert(std::pair<std::string, std::shared_ptr<Carteira>>(nome, conta));
}

void GerenciaConta::removerConta(std::string nome) {

    /*A funcao 'find' de um map retorna um ponteiro para map.end se nao encontrar nada*/
    if (this->getContas().find(nome) == this->getContas().end()) {
        throw gcexcp::ContaNaoEncontrada(nome);
    }

    getContas().erase(getContas().find(nome));
}

void GerenciaConta::adicionarReceita(std::string conta, double valor, std::string data,             
                                     std::string categoria) {

    if (this->getContas().find(conta) == this->getContas().end()) {
        throw gcexcp::ContaNaoEncontrada(conta);
    } else {
        double saldo_conta = getConta(conta)->getSaldoAtual();
        std::shared_ptr<Receita> receita = std::make_shared<Receita>(conta, valor, data, categoria);

        getConta(conta)->setSaldoAtual(saldo_conta + valor);
        getConta(conta)->adicionarTransacao(receita);
    }
}

void GerenciaConta::adicionarDespesa(std::string conta, double valor,
                                     std::string data, std::string categoria) {

    double saldo_conta = getConta(conta)->getSaldoAtual();
    std::shared_ptr<Despesa> despesa = std::make_shared<Despesa>(valor, data, categoria, conta);

    getConta(conta)->setSaldoAtual(saldo_conta - valor);
    getConta(conta)->adicionarTransacao(despesa);
}

void GerenciaConta::adicionarDespesaCartao(std::string conta, std::string cartao,
                                           double valor, std::string data,
                                           std::string categoria) {

    if (getConta(conta)->getSubtipo() == "ContaBancaria") {
        std::shared_ptr<ContaBancaria> conta_bancaria;
        conta_bancaria = std::dynamic_pointer_cast<ContaBancaria>(getConta(conta));
        conta_bancaria->getCartaoDeCredito(cartao).adicionarDespesa(valor, data, categoria);
    }
}

void GerenciaConta::adicionarTransferencia(double valor, std::string data, 
        std::string categoria, std::string origem, std::string destino) {

    std::shared_ptr<Transferencia> transferencia = std::make_shared<Transferencia>
        (valor, data, categoria, origem, destino);
    getTransferencias().insert(std::pair<int, std::shared_ptr<Transferencia>>
        (transferencia->getID(), transferencia));

    double saldo_conta_origem = getConta(origem)->getSaldoAtual();
    double saldo_conta_destino = getConta(destino)->getSaldoAtual();

    getConta(origem)->setSaldoAtual(saldo_conta_origem - valor);
    getConta(destino)->setSaldoAtual(saldo_conta_destino + valor);
}

void GerenciaConta::removerReceita(std::string conta, int id) {

    if (getConta(conta)->getTransacoes().find(id) == getConta(conta)->getTransacoes().end()) {
        throw trexcp::TransacaoNaoEncontrada(id);       
    } else {
        double valor = getConta(conta)->getTransacoes().find(id)->second->getValor();
        double saldo = getConta(conta)->getSaldoAtual() - valor;
        
        getConta(conta)->setSaldoAtual(saldo);
        getConta(conta)->removerTransacao(id);
    }
}

void GerenciaConta::removerDespesa(std::string conta, int id) {

    if (getConta(conta)->getTransacoes().find(id) == getConta(conta)->getTransacoes().end()) {
        throw trexcp::TransacaoNaoEncontrada(id);
    } else {
        double valor = getConta(conta)->getTransacoes().find(id)->second->getValor();
        double saldo = getConta(conta)->getSaldoAtual() + valor;
        
        getConta(conta)->setSaldoAtual(saldo);
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
    getTransferencias().erase(getTransferencias().find(id));
}

void GerenciaConta::adicionarCartao(std::string conta, std::string nome,
                                    std::string numero, std::string CVV,
                                    std::string fechamento, double limite_cartao) {

    if (getConta(conta)->getSubtipo() == "ContaBancaria") {
        std::shared_ptr<ContaBancaria> conta_bancaria;
        conta_bancaria = std::dynamic_pointer_cast<ContaBancaria>(getConta(conta));

        CartaoDeCredito cartao_de_credito(nome, numero, CVV, fechamento, limite_cartao);

        conta_bancaria->adicionarCartao(cartao_de_credito);
    }
}
void GerenciaConta::removerCartao(std::string conta, std::string cartao) {

    if (getConta(conta)->getSubtipo() == "ContaBancaria") {
        std::shared_ptr<ContaBancaria> conta_bancaria;
        conta_bancaria = std::dynamic_pointer_cast<ContaBancaria>(getConta(conta));

        conta_bancaria->removerCartao(cartao);
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
        for (auto const& conta : _contas) {
            conta.second->imprimirInfo();
        }
    } else {
        throw gcexcp::PerfilVazio();
    }
}

void GerenciaConta::listarTransacao(std::string conta, std::string tipo) {
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