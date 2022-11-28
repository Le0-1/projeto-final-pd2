#include "GerenciaConta.hpp"

GerenciaConta::GerenciaConta() { }

std::map<std::string, std::shared_ptr<Carteira>>& GerenciaConta::getContas() {
    return this->_contas;
}

std::map<int, Transferencia>& GerenciaConta::getTransferencias() {
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

void GerenciaConta::adicionarReceita(std::string conta, double valor,
                                     std::string data, std::string categoria) {

    double saldo_conta = getConta(conta)->getSaldoAtual();
    Receita receita(conta, valor, data, categoria);

    getConta(conta)->setSaldoAtual(saldo_conta + valor);
    getConta(conta)->adicionarTransacao(receita);
}

void GerenciaConta::adicionarDespesa(std::string conta, double valor,
                                     std::string data, std::string categoria) {

    double saldo_conta = getConta(conta)->getSaldoAtual();
    Despesa despesa(valor, data, categoria, conta);

    getConta(conta)->setSaldoAtual(saldo_conta - valor);
    getConta(conta)->adicionarTransacao(despesa);
}

void GerenciaConta::adicionarDespesaCartao(std::string conta, std::string cartao,
                                           double valor, std::string data,
                                           std::string categoria) {

    double saldo_conta = getConta(conta)->getSaldoAtual();
    Despesa despesa(valor, data, categoria, conta);

    getConta(conta)->setSaldoAtual(saldo_conta - valor);

    if (getConta(conta)->getSubtipo() == "ContaBancaria") {
        std::shared_ptr<ContaBancaria> conta_bancaria;
        conta_bancaria = std::dynamic_pointer_cast<ContaBancaria>(getConta(conta));
        conta_bancaria->getCartaoDeCredito(cartao).adicionarDespesa(valor, data, categoria);
    }
}

void GerenciaConta::adicionarTransferencia(double valor, std::string data, 
                                           std::string categoria, std::string origem,
                                           std::string destino) {

    Transferencia transferencia(valor, data, categoria, origem, destino);
    getTransferencias().insert(std::pair<int, Transferencia>(transferencia.getID(),
                                                             transferencia));

    double saldo_conta_origem = getConta(origem)->getSaldoAtual();
    double saldo_conta_destino = getConta(destino)->getSaldoAtual();

    getConta(origem)->setSaldoAtual(saldo_conta_origem - valor);
    getConta(destino)->setSaldoAtual(saldo_conta_destino + valor);
}

void GerenciaConta::removerReceita(std::string conta, int id) {
    getConta(conta)->removerTransacao(id);
}

void GerenciaConta::removerDespesa(std::string conta, int id) {
    getConta(conta)->removerTransacao(id);
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
    std::cout << "===============================================" << std::endl;

    for (auto const& conta : getContas()) {
        std::cout << conta.second->getNome() << std::endl;
    }
    std::cout << "===============================================" << std::endl;
}