#include "GerenciaConta.hpp"

#include "Utils.hpp"

#include <iostream>
#include <string>
#include <limits>

int main(int argc, char const *argv[]) {

    const std::string separador = "===========================================";
    const int corSeparador = Foreground::f_yellow;

    GerenciaConta gc;

    std::string input;
    Utils::limparConsole();

    while (input != "sair") {
        std::cin >> input;
        Utils::limparConsole();

        if (input == "add_carteira") {
            Utils::printColor(corSeparador, separador);
            Utils::printColor(Efeitos::inverse, "Nova carteira");
            std::cout << "nome, saldo inicial" << std::endl;

            std::string nome;
            double saldo_inicial;

            std::cin >> nome;
            std::cin >> saldo_inicial;

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

            catch (gcexcp::SaldoInvalido& e) {
                std::cout << e.what();
                std::cout << "\t Carteira: " << e.getNome();
                std::cout << "\t saldo: " << e.getSaldoInicial() << std::endl;    
            }
            Utils::printColor(corSeparador, separador);
            std::cout << std::endl;
        }

        if (input == "add_conta") {
            Utils::printColor(corSeparador, separador);
            Utils::printColor(Efeitos::inverse, "Nova conta");
            std::cout << "nome, saldo inicial" << std::endl;
            std::string nome;
            double saldo_inicial;

            std::cin >> nome;

            std::cin >> saldo_inicial;

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

            catch (gcexcp::SaldoInvalido& e) {
                std::cout << e.what();
                std::cout << "\t Conta: " << e.getNome();
                std::cout << "\t saldo: " << e.getSaldoInicial() << std::endl;
            }

            Utils::printColor(corSeparador, separador);
            std::cout << std::endl;
        }

        if (input == "rm_carteira") {
            Utils::printColor(corSeparador, separador);
            Utils::printColor(Efeitos::inverse, "Remover carteira");
            std::cout << "nome" << std::endl;
            
            std::string nome;
            std::cin >> nome;

            try {
                gc.removerConta(nome);
                std::cout << "Carteira removida" << std::endl;
            }
            catch (gcexcp::ContaNaoEncontrada& e) {
                std::cout << "Carteira não encontrada";
                std::cout << "\t Carteira: " << e.getNome() << std::endl;
            }

            Utils::printColor(corSeparador, separador);
            std::cout << std::endl;
        }

        if (input == "rm_conta") {
            Utils::printColor(corSeparador, separador);
            Utils::printColor(Efeitos::inverse, "Remover conta");
            std::cout << "nome" << std::endl;
            std::string nome;
            std::cin >> nome;

            try {
                gc.removerConta(nome);
                std::cout << "Conta removida" << std::endl;
            }
            
            catch (gcexcp::ContaNaoEncontrada& e) {
                std::cout << e.what();
                std::cout << "\t Conta: " << e.getNome() << std::endl;
            }

            Utils::printColor(corSeparador, separador);
            std::cout << std::endl;
        }

        if (input == "add_receita") {
            Utils::printColor(corSeparador, separador);
            Utils::printColor(Efeitos::inverse, "adicionar receita");
            std::cout << "conta, valor, data, categoria" << std::endl;

            std::string conta;
            double valor;
            std::string data;
            std::string categoria;

            std::cin >> conta;
            std::cin >> valor;

            while(std::cin.fail() || valor <= 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                std::cout << "Entrada Inválida. Coloque uma Receita: ";
                std::cin >> valor;
            }
            std::cin >> data;
            std::cin >> categoria;

            try {
                gc.adicionarReceita(conta, valor, data, categoria);
                std::cout << "Receita adicionada" << std::endl;
            }
            catch (gcexcp::ContaNaoEncontrada& e) {
                std::cout << e.what();
                std::cout << "\t Conta: " << e.getNome() << std::endl;
            }
            Utils::printColor(corSeparador, separador);
            std::cout << std::endl;
        }

        if (input == "add_despesa") {
            Utils::printColor(corSeparador, separador);
            Utils::printColor(Efeitos::inverse, "adicionar despesa");
            std::cout << "conta, valor, data, categoria" << std::endl;

            std::string conta;
            double valor;
            std::string data;
            std::string categoria;

            std::cin >> conta;
            std::cin >> valor;

            while(std::cin.fail() || valor <= 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                std::cout << "Entrada Inválida. Coloque uma Despesa: ";
                std::cin >> valor;
            }

            std::cin >> data;
            std::cin >> categoria;

            try {
                gc.adicionarDespesa(conta, valor, data, categoria);
                std::cout << "Despesa adicionada" << std::endl;
            }
            catch (gcexcp::ContaNaoEncontrada& e) {
                std::cout << e.what();
                std::cout << "\t Conta: " << e.getNome() << std::endl;
            }
            Utils::printColor(corSeparador, separador);
            std::cout << std::endl;
        }

        if (input == "add_despesa_cartao") {
            Utils::printColor(corSeparador, separador);
            Utils::printColor(Efeitos::inverse, "adicionar despesa cartao");
            std::cout << "conta, cartao, data, categoria, valor" << std::endl;

            std::string conta;
            std::string cartao;
            double valor;
            std::string data;
            std::string categoria;

            std::cin >> conta;
            std::cin >> cartao; 
            std::cin >> data;
            std::cin >> categoria;
            std::cin >> valor;

            while(std::cin.fail() || valor <= 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                std::cout << "Entrada Inválida. Coloque uma Despesa: ";
                std::cin >> valor;
            }

            try {
                gc.adicionarDespesaCartao(conta, cartao, valor, data, categoria);
                std::cout << "Despesa cartao de credito adicionada" << std::endl;
            }
            catch (gcexcp::ContaNaoEncontrada& e) {
                std::cout << e.what();
                std::cout << "\t Conta: " << e.getNome() << std::endl;
            }
            catch (cdcexcp::CartaoNaoEncontrado& e) {
                std::cout << e.what();
                std::cout << "\t Cartao: " << e.getNomeCartao() << std::endl;
            }
            catch (cdcexcp::LimiteExcedido& e) {
                std::cout << e.what();
                std::cout << "\t Limite restante do cartão " << e.getNomeCartao(); 
                std::cout << " é:"; // TO-DO LIMITE RESTANTE
            }
            Utils::printColor(corSeparador, separador);
            std::cout << std::endl;
        }

        if (input == "add_transferencia") {
            Utils::printColor(corSeparador, separador);
            Utils::printColor(Efeitos::inverse, "adicionar transferencia");
            std::cout << "valor, data, categoria, origem, destino" << std::endl;

            double valor;
            std::string data;
            std::string categoria;
            std::string origem;
            std::string destino;

            std::cin >> valor;
            std::cin >> data;
            std::cin >> categoria;
            std::cin >> origem;
            std::cin >> destino;

            gc.adicionarTransferencia(valor, data, categoria, origem, destino);

            std::cout << "transferencia adicionada" << std::endl;
            Utils::printColor(corSeparador, separador);
            std::cout << std::endl;
        }

        if (input == "rm_receita") {
            Utils::printColor(corSeparador, separador);
            Utils::printColor(Efeitos::inverse, "remover receita");
            std::cout << "conta,id" << std::endl;

            std::string conta;
            int id;

            std::cin >> conta;
            std::cin >> id;

            gc.removerReceita(conta, id);

            std::cout << "Receita removida" << std::endl;
            Utils::printColor(corSeparador, separador);
            std::cout << std::endl;
        }

        if (input == "rm_despesa") {
            Utils::printColor(corSeparador, separador);
            Utils::printColor(Efeitos::inverse, "remover despesa");
            std::cout << "conta, id" << std::endl;

            std::string conta;
            int id;

            std::cin >> conta;
            std::cin >> id;

            gc.removerDespesa(conta, id);

            std::cout << "Despesa removida" << std::endl;
            Utils::printColor(corSeparador, separador);
            std::cout << std::endl;
        }

        if (input == "rm_cartao_despesa") {
            Utils::printColor(corSeparador, separador);
            Utils::printColor(Efeitos::inverse, "remover despesa cartao de credito");
            std::cout << "conta, cartao, id " << std::endl;

            std::string conta;
            std::string cartao;
            int id;

            std::cin >> conta;
            std::cin >> cartao;
            std::cin >> id;

            gc.removerDespesaCartao(conta, cartao, id);

            std::cout << "Despea cartao removida" << std::endl;
            Utils::printColor(corSeparador, separador);
            std::cout << std::endl;
        }

        if (input == "rm_transferencia") {
            Utils::printColor(corSeparador, separador);
            Utils::printColor(Efeitos::inverse, "remover transferencia");
            std::cout << "conta, id " << std::endl;

            std::cout << "Transferencia removida" << std::endl;
            Utils::printColor(corSeparador, separador);
            std::cout << std::endl;
        }

        if (input == "add_cartao_credito") {
            Utils::printColor(corSeparador, separador);
            Utils::printColor(Efeitos::inverse, "adicionar cartao de credito");
            std::cout << "conta, nome, numero, CVV, fechamento, limite_cartao " << std::endl;

            std::string conta;
            std::string nome;
            std::string numero;
            std::string CVV;
            std::string fechamento;
            double limite_cartao;

            std::cin >> conta;
            std::cin >> nome;
            std::cin >> numero;
            std::cin >> CVV;
            std::cin >> fechamento;
            std::cin >> limite_cartao;

            while(std::cin.fail() || limite_cartao <= 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                std::cout << "Entrada Inválida. Coloque um Limite maior que zero: ";
                std::cin >> limite_cartao;
            }

            try {
            gc.adicionarCartao(conta, nome, numero, CVV, fechamento, limite_cartao);
            std::cout << "Cartao de credito criado" << std::endl;
            }
            catch (gcexcp::ContaNaoEncontrada& e) {
                std::cout << e.what();
                std::cout << "\t Conta: " << e.getNome() << std::endl;
            }
            catch (cdcexcp::LimiteInvalido& e) {
                std::cout << e.what() << std::endl;
                std::cout << "\t Limite digitado: " << e.getLimiteCartao() << std::endl;
            }
            Utils::printColor(corSeparador, separador);
            std::cout << std::endl;
        }

        if (input == "rm_cartao_credito") {
            Utils::printColor(corSeparador, separador);
            Utils::printColor(Efeitos::inverse, "remover cartao de credito");
            std::cout << "conta, nome, numero, CVV, fechamento, limite_cartao " << std::endl;

            std::string conta;
            std::string cartao;

            std::cin >> conta;
            std::cin >> cartao;

            gc.removerCartao(conta, cartao);

            std::cout << "Cartao de credito removido" << std::endl;
            Utils::printColor(corSeparador, separador);
            std::cout << std::endl;
        }

        if (input == "listar") {
            gc.imprimirContas();
        }

        if (input == "listar_transacao") {
            Utils::printColor(corSeparador, separador);
            Utils::printColor(Efeitos::inverse, "listar transacao");
            std::cout << "conta tipo" << std::endl;

            std::string conta;
            std::string tipo;

            std::cin >> conta;
            std::cin >> tipo;

            gc.listarTransacao(conta, tipo);
            Utils::printColor(corSeparador, separador);
            std::cout << std::endl;
        }
    }

    Utils::limparConsole();

    return 0;
}
