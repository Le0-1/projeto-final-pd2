#include "GerenciaConta.hpp"
#include "Utils.hpp"

#include <iostream>
#include <string>
#include <limits>

int main(int argc, char const *argv[]) {

    const std::string separador = "===========================================";
    const int corSeparador = Foreground::f_yellow;

    GerenciaConta gc;

    int input, id_transacao;
    double saldo_inicial, valor_transacao, limite_cartao;
    std::string nome, conta, data, categoria, cartao, destino, origem, CVV,
                fechamento, numero_cartao, tipo;

    Utils::limparConsole();

    while (std::cin >> input) {
        Utils::limparConsole();
        switch (input) {
            case 0: // Listar opcoes
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "MENU");
                std::cout << "1 - Adicionar carteira\n"
                          << "2 - Adicionar conta\n"
                          << "3 - Remover carteira\n"
                          << "4 - Remover conta\n"
                          << "5 - Adicionar receita\n"
                          << "6 - Adicionar despesa\n"
                          << "7 - Adicionar despesa cartao de credito\n"
                          << "8 - Adicionar transferencia\n"
                          << "9 - Remover receita\n"
                          << "10 - Remover despesa\n"
                          << "11 - Remover despesa cartao de credito\n"
                          << "12 - Remover transferencia\n"
                          << "13 - Adicionar cartao credito\n"
                          << "14 - Remover cartao de credito\n"
                          << "15 - Listar carteiras\n"
                          << "16 - Listas transacoes\n";
                Utils::printColor(corSeparador, separador);
                break;

            case 1: // Adicionar carteira
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "Nova carteira");
                std::cout << "nome, saldo inicial" << std::endl;

                std::cin >> nome >> saldo_inicial;

                while(std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout << "Entrada Inválida. Coloque um valor: ";
                    std::cin >> saldo_inicial;
                }

                try {
                    gc.adicionarCarteira(nome, saldo_inicial);
                    std::cout << "Carteira criada" << std::endl;
                }
                catch (gcexcp::ValorInvalido& e) {
                    std::cout << e.what()
                              << "\t Carteira: " << e.getNome()
                              << "\t saldo: " << e.getValor()
                              << std::endl;
                }
                catch (gcexcp::ContaJaExiste &e) {
                     std::cout << e.what()
                               << "\t Nome: " << e.getNome()
                               << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                break;

            case 2: // Adicionar conta
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "Nova conta");
                std::cout << "nome, saldo inicial" << std::endl;

                std::cin >> nome >> saldo_inicial;

                while(std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout << "Entrada Inválida. Coloque um valor: ";
                    std::cin >> saldo_inicial;
                }

                try {
                    gc.adicionarConta(nome, saldo_inicial);
                    std::cout << "Conta criada" << std::endl;
                }
                catch (gcexcp::ValorInvalido& e) {
                    std::cout << e.what()
                              << "\t Conta: " << e.getNome()
                              << "\t saldo: " << e.getValor()
                              << std::endl;
                }
                catch (gcexcp::ContaJaExiste &e) {
                    std::cout << e.what()
                              << "\t Nome: " << e.getNome()
                              << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                break;

            case 3: // Remover carteira
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "Remover carteira");
                std::cout << "nome" << std::endl;

                std::cin >> nome;

                try {
                    gc.removerConta(nome);
                    std::cout << "Carteira removida" << std::endl;
                }
                catch (gcexcp::ContaNaoEncontrada& e) {
                    std::cout << "Carteira não encontrada"
                              << "\t Carteira: " << e.getNome()
                              << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                break;

            case 4: // Remover conta
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "Remover conta");
                std::cout << "nome" << std::endl;
                std::cin >> nome;

                try {
                    gc.removerConta(nome);
                    std::cout << "Conta removida" << std::endl;
                }
                catch (gcexcp::ContaNaoEncontrada& e) {
                    std::cout << e.what()
                              << "\t Conta: " << e.getNome()
                              << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                break;

            case 5: // Adicionar receita
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "adicionar receita");
                std::cout << "conta, valor, data, categoria" << std::endl;

                std::cin >> conta >> valor_transacao;

                while (std::cin.fail() || valor_transacao <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout << "Entrada Inválida. Coloque um valor valido, data, categoria: ";
                    std::cin >> valor_transacao;
                }

                std::cin >> data >> categoria;

                try {
                    gc.adicionarReceita(conta, valor_transacao, data, categoria);
                    std::cout << "Receita adicionada" << std::endl;
                }
                catch (gcexcp::ContaNaoEncontrada& e) {
                    std::cout << e.what()
                              << "\t Conta: " << e.getNome()
                              << std::endl;
                }
                catch (gcexcp::ValorInvalido &e) {
                    std::cout << e.what()
                              << "\t Valor: " << e.getValor()
                              << std::endl;
                }
                catch (gcexcp::ContaNaoPermiteCartao &e) {
                    std::cout << e.what()
                              << "\t Conta: " << e.getNomeConta()
                              << "\t Subtipo: " << e.getSubtipoConta()
                              << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                break;

            case 6: // Adicionar despesa
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "adicionar despesa");
                std::cout << "conta, valor, data, categoria" << std::endl;

                std::cin >> conta;
                std::cin >> valor_transacao;

                while(std::cin.fail() || valor_transacao <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout << "Entrada Inválida. Coloque uma Despesa: ";
                    std::cin >> valor_transacao;
                }

                std::cin >> data >> categoria;

                try {
                    gc.adicionarDespesa(conta, valor_transacao, data, categoria);
                    std::cout << "Despesa adicionada" << std::endl;
                }
                catch (gcexcp::ContaNaoEncontrada& e) {
                    std::cout << e.what()
                              << "\t Conta: " << e.getNome()
                              << std::endl;
                }
                catch (gcexcp::SaldoInsuficiente &e) {
                    std::cout << e.what()
                              << "\t Diferença: " << e.getSaldo() - e.getDespesa()
                              << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                break;

            case 7: // Adicionar despesa cartao de credito
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "adicionar despesa cartao");
                std::cout << "conta, cartao, data, categoria, valor" << std::endl;

                std::cin >> conta >> cartao >> data >> categoria >> valor_transacao;

                while(std::cin.fail() || valor_transacao <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout << "Entrada Inválida. Coloque uma Despesa: ";
                    std::cin >> valor_transacao;
                }

                try {
                    gc.adicionarDespesaCartao(conta, cartao, valor_transacao, data, categoria);
                    std::cout << "Despesa cartao de credito adicionada" << std::endl;
                }
                catch (gcexcp::ContaNaoEncontrada& e) {
                    std::cout << e.what()
                              << "\t Conta: " << e.getNome()
                              << std::endl;
                }
                catch (cdcexcp::CartaoNaoEncontrado& e) {
                    std::cout << e.what()
                              << "\t Cartao: " << e.getNomeCartao()
                              << std::endl;
                }
                catch (cdcexcp::LimiteExcedido& e) {
                    std::cout << e.what()
                              << "\n Limite restante do cartão " << e.getNomeCartao()
                              << " é: " << e.getLimiteCartao() - e.getSomaDespesasAtuais
                              << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                break;

            case 8: // Adicionar transferencia
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "adicionar transferencia");
                std::cout << "valor, data, categoria, origem, destino" << std::endl;

                std::cin >> valor_transacao >> data >> categoria >> origem >> destino;

                gc.adicionarTransferencia(valor_transacao, data, categoria, origem, destino);
                std::cout << "transferencia adicionada" << std::endl;

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                break;

            case 9: // Remover receita
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "remover receita");
                std::cout << "conta,id" << std::endl;

                std::cin >> conta >> id_transacao;
                gc.removerReceita(conta, id_transacao);

                std::cout << "Receita removida" << std::endl;
                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                break;

            case 10: // Remover despesa
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "remover despesa");
                std::cout << "conta, id" << std::endl;

                std::cin >> conta >> id_transacao;

                gc.removerDespesa(conta, id_transacao);

                std::cout << "Despesa removida" << std::endl;
                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                break;

            case 11: // Remover despesa cartao de credito
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "remover despesa cartao de credito");
                std::cout << "conta, cartao, id " << std::endl;

                std::cin >> conta >> cartao >> id_transacao;

                gc.removerDespesaCartao(conta, cartao, id_transacao);

                std::cout << "Despea cartao removida" << std::endl;
                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                break;

            case 12: // Remover transferencia
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "remover transferencia");
                std::cout << "conta, id " << std::endl;

                std::cout << "Transferencia removida" << std::endl;
                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                break;

            case 13: // Adicionar cartao de credito
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "adicionar cartao de credito");
                std::cout << "conta, nome, numero, CVV, fechamento, limite_cartao " << std::endl;

                std::cin >> conta >> nome >> numero_cartao >> CVV >> fechamento >> limite_cartao;

                while(std::cin.fail() || limite_cartao <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout << "Entrada Inválida. Coloque um Limite maior que zero: ";
                    std::cin >> limite_cartao;
                }

                try {
                    gc.adicionarCartao(conta, nome, numero_cartao, CVV, fechamento, limite_cartao);
                    std::cout << "Cartao de credito criado" << std::endl;
                }
                catch (gcexcp::ContaNaoEncontrada& e) {
                    std::cout << e.what()
                              << "\t Conta: " << e.getNome()
                              << std::endl;
                }
                catch (cdcexcp::LimiteInvalido& e) {
                    std::cout << e.what()
                              << std::endl
                              << "\t Limite digitado: " << e.getLimiteCartao()
                              << std::endl;
                }
                catch (cdcexcp::NumeroInvalido& e) {
                    std::cout << e.what()
                              << std::endl
                              << "\t Número digitado: " << e.getNumero()
                              << std::endl;
                }
                catch (cdcexcp::CVVInvalido& e) {
                    std::cout << e.what()
                              << std::endl
                              << "\t CVV digitado: " << e.getCVV()
                              << std::endl;
                }
                catch (cdcexcp::FechamentoInvalido& e) {
                    std::cout << e.what()
                              << std::endl
                              << "\t Fechamento digitado: " << e.getFechamento()
                              << std::endl;
                }
                catch (gcexcp::ContaNaoPermiteCartao &e) {
                    std::cout << e.what()
                              << "\t Conta: " << e.getNomeConta()
                              << "\t Subtipo: " << e.getSubtipoConta()
                              << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                break;

            case 14: // Remover cartao de credito
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "remover cartao de credito");
                std::cout << "conta, nome" << std::endl;

                std::cin >> conta >> cartao;

                try {
                    gc.removerCartao(conta, cartao);
                    std::cout << "Cartao de credito removido" << std::endl;
                }
                catch (gcexcp::ContaNaoEncontrada &e) {
                    std::cout << e.what()
                              << "\t Conta: " << e.getNome()
                              << std::endl;
                }
                catch (cdcexcp::CartaoNaoEncontrado &e) {
                    std::cout << e.what()
                              << "\t Cartao: " << e.getNomeCartao()
                              << std::endl;
                }
                catch (gcexcp::ContaNaoPermiteCartao &e) {
                    std::cout << e.what()
                              << "\t Conta: " << e.getNomeConta()
                              << "\t Subtipo: " << e.getSubtipoConta()
                              << std::endl;
                }
                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                break;

            case 15: // Listar constas
                try {
                    gc.imprimirContas();
                }
                catch (gcexcp::PerfilVazio &e) {
                    std::cout << e.what() << std::endl;
                }
                Utils::printColor(corSeparador, separador);
                break;

            case 16: // Listar transacoes
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "listar transacao");
                std::cout << "conta tipo" << std::endl;

                std::cin >> conta >> tipo;

                try {
                    gc.listarTransacao(conta, tipo);
                }
                catch (gcexcp::ContaNaoEncontrada &e) {
                    std::cout << e.what()
                              << "\t Conta: " << e.getNome()
                              << std::endl;
                }
                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                break;
        }
    }

    Utils::limparConsole();

    return 0;
}
