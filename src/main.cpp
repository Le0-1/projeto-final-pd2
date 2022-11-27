#include "GerenciaConta.hpp"

#include <iostream>
#include <string>
#include <limits>

int main(int argc, char const *argv[]) {

    GerenciaConta gc;

    std::string input;

    while (input != "sair") {
        std::cin >> input;
        if (input == "add_carteira") {
            std::cout << "=======================================" << std::endl;
            std::cout << "Nova carteira" << std::endl;
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
            std::cout << "=======================================" << std::endl;
            std::cout << std::endl;
        }

        if (input == "add_conta") {
            std::cout << "=======================================" << std::endl;
            std::cout << "Nova conta" << std::endl;
            std::cout << "nome, saldo inicial" << std::endl;
            std::string nome;
            double saldo_inicial;

            std::cin >> nome;
            std::cin >> saldo_inicial;

            gc.adicionarConta(nome, saldo_inicial);

            std::cout << "Conta criada" << std::endl;
            std::cout << "=======================================" << std::endl;
            std::cout << std::endl;
        }

        if (input == "rm_carteira") {
            std::cout << "=======================================" << std::endl;
            std::cout << "Remover carteira" << std::endl;
            std::cout << "nome" << std::endl;
            std::string nome;
            std::cin >> nome;

            gc.removerConta(nome);
            std::cout << "Carteira removida" << std::endl;
            std::cout << "=======================================" << std::endl;
            std::cout << std::endl;
        }

        if (input == "rm_conta") {
            std::cout << "=======================================" << std::endl;
            std::cout << "Remover conta" << std::endl;
            std::cout << "nome" << std::endl;
            std::string nome;
            std::cin >> nome;

            gc.removerConta(nome);
            std::cout << "Conta removida" << std::endl;
            std::cout << "=======================================" << std::endl;
            std::cout << std::endl;
        }

        if (input == "add_receita") {
            std::cout << "=======================================" << std::endl;
            std::cout << "adicionar receita" << std::endl;
            std::cout << "conta, valor, descricao, data, categoria" << std::endl;

            std::string conta;
            double valor;
            std::string data;
            std::string categoria;

            std::cin >> conta;
            std::cin >> valor;
            std::cin >> data;
            std::cin >> categoria;

            gc.adicionarReceita(conta, valor, data, categoria);

            std::cout << "Receita adicionada" << std::endl;
            std::cout << "=======================================" << std::endl;
            std::cout << std::endl;
        }

        if (input == "add_despesa") {
            std::cout << "=======================================" << std::endl;
            std::cout << "adicionar despesa" << std::endl;
            std::cout << "conta, valor, descricao, data, categoria" << std::endl;

            std::string conta;
            double valor;
            std::string data;
            std::string categoria;

            std::cin >> conta;
            std::cin >> valor;
            std::cin >> data;
            std::cin >> categoria;

            gc.adicionarDespesa(conta, valor, data, categoria);

            std::cout << "Despesa adicionada" << std::endl;
            std::cout << "=======================================" << std::endl;
            std::cout << std::endl;
        }

        if (input == "add_despesa_cartao") {
            std::cout << "=======================================" << std::endl;
            std::cout << "adicionar despesa" << std::endl;
            std::cout << "conta, valor, descricao, data, categoria" << std::endl;

            std::string conta;
            double valor;
            std::string data;
            std::string categoria;

            std::cin >> conta;
            std::cin >> valor;
            std::cin >> data;
            std::cin >> categoria;

            gc.adicionarDespesa(conta, valor, data, categoria);

            std::cout << "Despesa adicionada" << std::endl;
            std::cout << "=======================================" << std::endl;
            std::cout << std::endl;
        }

        if (input == "add_transferencia") {
            std::cout << "=======================================" << std::endl;
            std::cout << "adicionar transferencia" << std::endl;
            std::cout << "valor, descricao, data, categoria, origem, destino" << std::endl;

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
            std::cout << "=======================================" << std::endl;
            std::cout << std::endl;
        }

        if (input == "rm_receita") {
            std::cout << "=======================================" << std::endl;
            std::cout << "remver receita" << std::endl;
            std::cout << "conta,id" << std::endl;

            std::string conta;
            int id;

            std::cin >> conta;
            std::cin >> id;

            gc.removerReceita(conta, id);

            std::cout << "Receita removida" << std::endl;
            std::cout << "=======================================" << std::endl;
            std::cout << std::endl;
        }

        if (input == "rm_despesa") {
            std::cout << "=======================================" << std::endl;
            std::cout << "remover despesa" << std::endl;
            std::cout << "conta, id" << std::endl;

            std::string conta;
            int id;

            std::cin >> conta;
            std::cin >> id;

            gc.removerDespesa(conta, id);

            std::cout << "Despesa removida" << std::endl;
            std::cout << "=======================================" << std::endl;
            std::cout << std::endl;
        }

        if (input == "rm_cartao_despesa") {
            std::cout << "=======================================" << std::endl;
            std::cout << "remover despesa cartao de credito" << std::endl;
            std::cout << "conta, cartao, id " << std::endl;

            std::string conta;
            std::string cartao;
            int id;

            std::cin >> conta;
            std::cin >> cartao;
            std::cin >> id;

            gc.removerDespesaCartao(conta, cartao, id);

            std::cout << "Despea cartao removida" << std::endl;
            std::cout << "=======================================" << std::endl;
            std::cout << std::endl;
        }

        if (input == "rm_transferencia") {
            std::cout << "=======================================" << std::endl;
            std::cout << "remover transferencia" << std::endl;
            std::cout << "conta, id " << std::endl;

            std::cout << "Transferencia removida" << std::endl;
            std::cout << "=======================================" << std::endl;
            std::cout << std::endl;
        }

        if (input == "add_cartao_despesa") {
            std::cout << "=======================================" << std::endl;
            std::cout << "adicionar cartao de credito" << std::endl;
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

            gc.adicionarCartao(conta, nome, numero, CVV, fechamento, limite_cartao);
            std::cout << "Cartao de credito criado" << std::endl;
            std::cout << "=======================================" << std::endl;
            std::cout << std::endl;
        }

        if (input == "rm_cartao_credito") {
            std::cout << "=======================================" << std::endl;
            std::cout << "remover cartao de credito" << std::endl;
            std::cout << "conta, nome, numero, CVV, fechamento, limite_cartao " << std::endl;

            std::string conta;
            std::string cartao;

            std::cin >> conta;
            std::cin >> cartao;

            gc.removerCartao(conta, cartao);

            std::cout << "Cartao de credito removido" << std::endl;
            std::cout << "=======================================" << std::endl;
            std::cout << std::endl;
        }
    }
    
    return 0;
}
