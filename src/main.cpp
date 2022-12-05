#include "GerenciaConta.hpp"
#include "Utils.hpp"
#include "Barricada.hpp"

#include <iostream>
#include <string>


void printMenu();
void printMensagem();

int main(int argc, char const *argv[]) {

    const std::string separador = "===========================================";
    const int corSeparador = Foreground::f_yellow;

    GerenciaConta gc;

    unsigned input, id_transacao;
    double saldo_inicial, valor_transacao, limite_cartao;
    std::string nome, conta, data, categoria, cartao, destino, origem, CVV,
                fechamento, numero_cartao, tipo;

    Utils::limparConsole();

    Utils::printColor(corSeparador, separador);
    printMenu();
    Utils::printColor(corSeparador, separador);

    while (1) {

        std::cin >> input;

        /*Barricada que irá validar o input para ver se ele é menor que 0 ou maior que 16*/
        Barricada::validar_input(input);

        Utils::limparConsole();

        switch (input) {

            case 0: // Listar opcoes
                Utils::printColor(corSeparador, separador);
                printMenu();
                Utils::printColor(corSeparador, separador);
                continue;

            case 1: // Adicionar carteira
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "-------------- NOVA CARTEIRA --------------");

                Utils::printColorNoLine(Efeitos::bold_bright, "NOME CARTEIRA: ");
                std::cin >> nome;
                Utils::printColorNoLine(Efeitos::bold_bright, "SALDO INICIAL: ");
                std::cin >> saldo_inicial;

                /*Barricada que verifica o valor do saldo*/
                Barricada::validar_saldo(saldo_inicial);

                try {
                    gc.adicionarCarteira(nome, saldo_inicial);
                    Utils::printColor(Foreground::f_green, "CARTEIRA ADICIONADA ✔️");
                }

                catch (ctrexcp::ValorInvalido& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "SALDO: "); 
                    std::cout << e.getValor() << std::endl;
                }

                catch (ctrexcp::ContaJaExiste &e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "CONTA: "); 
                    std::cout << e.getNome() << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 2: // Adicionar carteira bancária
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "--------------- NOVA CONTA ----------------");

                Utils::printColorNoLine(Efeitos::bold_bright, "NOME CARTEIRA: ");
                std::cin >> nome;
                Utils::printColorNoLine(Efeitos::bold_bright, "SALDO INICIAL: ");
                std::cin >> saldo_inicial;

                /*Barricada que verifica o valor da transacao*/
                Barricada::validar_saldo(saldo_inicial);

                try {
                    gc.adicionarConta(nome, saldo_inicial);
                    Utils::printColor(Foreground::f_green, "CARTEIRA BANCÁRIA ADICIONADA ✔️");
                }
                catch (ctrexcp::ValorInvalido& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "SALDO: "); 
                    std::cout << e.getValor() << std::endl;
                }
                catch (ctrexcp::ContaJaExiste &e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "CONTA: "); 
                    std::cout << e.getNome() << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 3: // Adicionar receita
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "----------- ADICIONAR RECEITA -------------");
                // std::cout << "CONTA, VALOR, DATA, CATEGORIA" << std::endl;

                //std::cin >> conta >> valor_transacao;

                Utils::printColorNoLine(Efeitos::bold_bright, "CONTA: ");
                std::cin >> conta;
                Utils::printColorNoLine(Efeitos::bold_bright, "VALOR: ");
                std::cin >> valor_transacao;

                /*Barricada que verifica o valor da transacao*/
                Barricada::validar_transacao(valor_transacao);

                Barricada::selecionarData(data);

                Utils::printColorNoLine(Efeitos::bold_bright, "CATEGORIA: ");
                std::cin >> categoria;

                try {
                    gc.adicionarReceita(conta, valor_transacao, data, categoria);
                    Utils::printColor(Foreground::f_green, "RECEITA ADICIONADA ✔️");
                }
                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "CONTA: ");
                    std::cout << e.getNome() << std::endl;
                }
                catch (ctrexcp::ValorInvalido& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "SALDO: "); 
                    std::cout << e.getValor() << std::endl;
                }
                catch (ctrexcp::ContaNaoPermiteCartao &e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "CONTA: ");
                    std::cout << e.getNomeConta();
                    Utils::printColorNoLine(Foreground::f_red, "\t SUBTIPO: ");
                    std::cout << e.getSubtipoConta() << std::endl;
                    
                }
                catch (trsexcp::DataInvalida &e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColor(Foreground::f_red, "DATA: ");
                    std::cout << e.getData() << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 4: // Adicionar despesa
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "------------ ADICIONAR DESPESA ------------");
                // std::cout << "CONTA, VALOR, DATA, CATEGORIA" << std::endl;

                Utils::printColorNoLine(Efeitos::bold_bright, "CONTA: ");
                std::cin >> conta;
                Utils::printColorNoLine(Efeitos::bold_bright, "VALOR: ");
                std::cin >> valor_transacao;

                /*Barricada que verifica o valor da transacao*/
                Barricada::validar_transacao(valor_transacao);

                Barricada::selecionarData(data);

                Utils::printColorNoLine(Efeitos::bold_bright, "CATEGORIA: ");
                std::cin >> categoria;


                try {
                    gc.adicionarDespesa(conta, valor_transacao, data, categoria);
                    Utils::printColor(Foreground::f_green, "DESPESA ADICIONADA ✔️");
                }

                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "CONTA: ");
                    std::cout << e.getNome() << std::endl;
                }

                catch (ctrexcp::ValorInvalido& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "SALDO: "); 
                    std::cout << e.getValor() << std::endl;
                }

                catch (ctrexcp::SaldoInsuficiente &e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "DIFERENÇA: ");
                    std::cout << e.getSaldo() - e.getDespesa() << std::endl;
                } 
                catch (trsexcp::DataInvalida &e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "DATA: ");
                    std::cout << e.getData() << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 5: // Adicionar despesa cartao de credito
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "--- ADICIONAR DESPESA CARTAO DE CREDITO ---");
                // std::cout << "CONTA, CARTAO, DATA, CATEGORIA, VALOR" << std::endl;

                Utils::printColorNoLine(Efeitos::bold_bright, "CONTA: ");
                std::cin >> conta;
                Utils::printColorNoLine(Efeitos::bold_bright, "CARTÃO: ");
                std::cin >> cartao;

                Barricada::selecionarData(data);

                Utils::printColorNoLine(Efeitos::bold_bright, "CATEGORIA: ");
                std::cin >> categoria;
                Utils::printColorNoLine(Efeitos::bold_bright, "VALOR: ");
                std::cin >> valor_transacao;

                /*Barricada que verifica o valor da transacao*/
                Barricada::validar_transacao(valor_transacao);

                try {
                    gc.adicionarDespesaCartao(conta, cartao, valor_transacao, data, categoria);
                    Utils::printColor(Foreground::f_green, "DESPESA CARTÃO DE CRÉDITO ADICIONADA ✔️");
                }

                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "CONTA: ");
                    std::cout << e.getNome() << std::endl;
                }

                catch (cdcexcp::CartaoNaoEncontrado& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "CARTÃO: ");
                    std::cout << e.getNomeCartao() << std::endl;  
                }

                catch (cdcexcp::LimiteExcedido& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "LIMITE RESTANTE DO CARTÃO "); 
                    std::cout << e.getNomeCartao();
                    Utils::printColorNoLine(Foreground::f_red, " É: ");
                    std:: cout << e.getLimiteCartao() - e.getSomaDespesasAtuais << std::endl;
                }
                catch (trsexcp::DataInvalida &e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColor(Foreground::f_red, "DATA: ");
                    std::cout << e.getData() << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 6: // Adicionar transferencia
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "--------- ADICIONAR TRANSFERENCIA ---------");
                // std::cout << "VALOR, DATA, CATEGORIA, ORIGEM, DESTINO" << std::endl;

                Utils::printColorNoLine(Efeitos::bold_bright, "VALOR: ");
                std::cin >> valor_transacao;

                /*Barricada que verifica o valor da transacao*/
                Barricada::validar_transacao(valor_transacao);
                Barricada::selecionarData(data);

                Utils::printColorNoLine(Efeitos::bold_bright, "CATEGORIA: ");
                std::cin >> categoria;
                Utils::printColorNoLine(Efeitos::bold_bright, "ORIGEM: ");
                std::cin >> origem;
                Utils::printColorNoLine(Efeitos::bold_bright, "DESTINO: ");
                std::cin >> destino;

                try {
                    gc.adicionarTransferencia(valor_transacao, data, categoria, origem, destino);
                    Utils::printColor(Foreground::f_green, "TRANSFERÊNCIA ADICIONADA ✔️");
                }

                catch (trfexcp::TransferenciaInvalida& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "CONTA ORIGEM IGUAL AO DESTINO: ");
                    std::cout << e.getNomeConta() << std::endl;
                }

                catch (ctrexcp::ValorInvalido& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColor(Foreground::f_red, "TRANSFERÊNCIA DEIXA SALDO NO NEGATIVO");
                    Utils::printColorNoLine(Foreground::f_red, "CONTA: "); 
                    std::cout << e.getNome();
                    Utils::printColorNoLine(Foreground::f_red, "\tVALOR: "); 
                    std::cout << e.getValor();
                    Utils::printColorNoLine(Foreground::f_red, "\tVALOR DA TRANSAÇÃO: "); 
                    std::cout << valor_transacao << std::endl;
                }

                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "CONTA: ");
                    std::cout << e.getNome() << std::endl;
                } 

                catch (trsexcp::DataInvalida &e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColor(Foreground::f_red, "DATA: ");
                    std::cout << e.getData() << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 7: // Adicionar cartao de credito
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "------- ADICIONAR CARTAO DE CREDITO -------");
                //std::cout << "CONTA, NOME, NUMERO, CVV, FECHAMENTO,\nLIMITE CARTAO" << std::endl;

                //std::cin >> conta >> nome >> numero_cartao >> CVV >> fechamento >> limite_cartao;

                Utils::printColorNoLine(Efeitos::bold_bright, "CONTA: ");
                std::cin >> conta;
                Utils::printColorNoLine(Efeitos::bold_bright, "NOME CARTÃO: ");
                std::cin >> nome;
                Utils::printColorNoLine(Efeitos::bold_bright, "NÚMERO CARTÃO: ");
                std::cin >> numero_cartao;
                Utils::printColorNoLine(Efeitos::bold_bright, "CVV CARTÃO: ");
                std::cin >> CVV;
                Utils::printColorNoLine(Efeitos::bold_bright, "FECHAMENTO CARTÃO: ");
                std::cin >> fechamento;
                Utils::printColorNoLine(Efeitos::bold_bright, "LIMITE CARTÃO: ");
                std::cin >> limite_cartao;

                /*Barricada que irá verificar o valor do limite passado*/
                Barricada::validar_limite_cartao(limite_cartao);

                try {
                    gc.adicionarCartao(conta, nome, numero_cartao, CVV, fechamento, limite_cartao);
                    Utils::printColor(Foreground::f_green, "CARTÃO DE CRÉDITO CRIADO ✔️");
                }

                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "CONTA: ");
                    std::cout << e.getNome() << std::endl;
                }

                catch (cdcexcp::LimiteInvalido& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "LIMITE DIGITADO: "); 
                    std::cout << e.getLimiteCartao() << std::endl;
                }

                catch (cdcexcp::NumeroInvalido& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "NÚMERO DIGITADO: "); 
                    std::cout << e.getNumero() << std::endl;
                }

                catch (cdcexcp::CVVInvalido& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "CVV DIGITADO: "); 
                    std::cout << e.getCVV() << std::endl;          
                }

                catch (cdcexcp::FechamentoInvalido& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "FECHAMENTO DIGITADO: "); 
                    std::cout << e.getFechamento() << std::endl;
                              
                }

                catch (ctrexcp::ContaNaoPermiteCartao &e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "CONTA: ");
                    std::cout << e.getNomeConta();
                    Utils::printColorNoLine(Foreground::f_red, "\tSUBTIPO: ");
                    std::cout << e.getSubtipoConta() << std::endl;
                    
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 8: // Remover carteira
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, 
                                 "------------ REMOVER CARTEIRA -------------");
                Utils::printColorNoLine(Efeitos::bold_bright, "NOME: ");
                std::cin >> nome;

                try {
                    gc.removerConta(nome);
                    Utils::printColor(Foreground::f_green, "CARTEIRA REMOVIDA ✔️");
                }

                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "CONTA: ");
                    std::cout << e.getNome() << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 9: // Remover carteira bancária
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "--------------- REMOVER CONTA -------------");
                Utils::printColorNoLine(Efeitos::bold_bright, "CARTEIRA BANCÁRIA: ");
                std::cin >> nome;

                try {
                    gc.removerConta(nome);
                    Utils::printColor(Foreground::f_green, "CARTEIRA BANCÁRIA REMOVIDA ✔️");
                }

                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColor(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, "CONTA: ");
                    std::cout << e.getNome() << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 10: // Remover receita
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "------------- REMOVER RECEITA -------------");
                std::cout << "CONTA, ID" << std::endl;

                std::cin >> conta >> id_transacao;

                /*Barricada que irá verificar a validade do ID passado*/
                Barricada::validar_id(id_transacao);

                try {
                    gc.removerReceita(conta, id_transacao);
                    std::cout << "Receita removida" << std::endl;
                }

                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Carteira: " << e.getNome()
                    << std::endl;
                }

                catch (trsexcp::TransacaoNaoEncontrada& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t ID da Transacao: " << e.getID()
                    << std::endl;
                }

                catch (trsexcp::TipoTransacaoInvalido& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Transacao: " << e.getTipo()
                    << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 11: // Remover despesa
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "------------- REMOVER DESPESA -------------");
                std::cout << "CONTA, ID" << std::endl;

                std::cin >> conta >> id_transacao;

                /*Barricada que irá verificar a validade do ID passado*/
                Barricada::validar_id(id_transacao);

                try {
                    gc.removerDespesa(conta, id_transacao);
                    std::cout << "Despesa removida" << std::endl;
                }

                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Carteira: " << e.getNome()
                    << std::endl;
                }

                catch (trsexcp::TransacaoNaoEncontrada& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t ID da Transacao: " << e.getID()
                    << std::endl;
                }

                catch (trsexcp::TipoTransacaoInvalido& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Transacao: " << e.getTipo()
                    << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 12: // Remover despesa cartao de credito
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "---- REMOVER DESPESA CARTAO DE CREDITO ----");
                std::cout << "CONTA, CARTAO, ID" << std::endl;

                std::cin >> conta >> cartao >> id_transacao;

                /*Barricada que irá verificar a validade do ID passado*/
                Barricada::validar_id(id_transacao);

                try {
                    gc.removerDespesaCartao(conta, cartao, id_transacao);
                    std::cout << "Despesa cartao removida" << std::endl;
                }

                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Carteira: " << e.getNome()
                    << std::endl;
                }

                catch (cdcexcp::CartaoNaoEncontrado &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Cartao: " << e.getNomeCartao()
                    << std::endl;
                }

                catch (trsexcp::TransacaoNaoEncontrada& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t ID da Transacao: " << e.getID()
                    << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 13: // Remover transferencia
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "---------- REMOVER TRANSFERENCIA ----------");
                std::cout << "CONTA, ID" << std::endl;

                std::cin >> conta >> id_transacao;

                /*Barricada que irá verificar a validade do ID passado*/
                Barricada::validar_id(id_transacao);

                try {
                    gc.removerTransferencia(conta,id_transacao);
                    std::cout << "Transferencia removida" << std::endl;
                }

                catch (trsexcp::TransacaoNaoEncontrada &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t ID: " << e.getID()
                    << std::endl;
                }

                catch (ctrexcp::SaldoInsuficiente &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\n Saldo na conta de destino R$" << e.getSaldo()
                    << "\n Valor que deve ser debitado R$" << e.getDespesa()
                    << std::endl;
                }

                catch (trfexcp::TransferenciaInvalida& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    Utils::printColorNoLine(Foreground::f_red, ", ID não é de uma transferência");
                    std::cout << "\t Conta: " << e.getNomeConta()
                    << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;


            case 14: // Remover cartao de credito
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "-------- REMOVER CARTAO DE CREDITO --------");
                std::cout << "CONTA, NOME" << std::endl;

                std::cin >> conta >> cartao;

                try {
                    gc.removerCartao(conta, cartao);
                    std::cout << "Cartao de credito removido" << std::endl;
                }

                catch (ctrexcp::ContaNaoEncontrada &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Conta: " << e.getNome()
                    << std::endl;
                }

                catch (cdcexcp::CartaoNaoEncontrado &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Cartao: " << e.getNomeCartao()
                    << std::endl;
                }

                catch (ctrexcp::ContaNaoPermiteCartao &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Conta: " << e.getNomeConta()
                    << "\t Subtipo: " << e.getSubtipoConta()
                    << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 15: // Pagar fatura do cartão
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "-------------- PAGAR FATURA ---------------");
                std::cout << "CONTA, CARTAO" << std::endl;

                std::cin >> conta >> cartao;

                try {
                    gc.pagarFaturaCartao(conta, cartao);
                    std::cout << "Fatura do cartao de credito paga" << std::endl;
                }
                catch (ctrexcp::ContaNaoEncontrada &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Conta: " << e.getNome()
                    << std::endl;
                }
                catch (cdcexcp::CartaoNaoEncontrado &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Cartao: " << e.getNomeCartao()
                    << std::endl;
                }
                catch (ctrexcp::SaldoInsuficiente &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\nSaldo na conta de destino R$" << e.getSaldo()
                    << "\nValor que deve ser debitado R$" << e.getDespesa()
                    << std::endl;
                }
                catch (ctrexcp::ContaNaoPermiteCartao &e) {
                    // Remover catch quando for possivel pagar fatura a carteira
                    Utils::printColorNoLine(Foreground::f_red, 
                            "Nao eh possivel pagar fatura com conta do tipo carteira");
                    std::cout << std::endl;
                }
               
                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                continue;

            case 16: // Listar carteiras
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "------------ LISTAR CARTEIRAS -------------");

                try {
                    gc.imprimirContas();
                }
                catch (gcexcp::PerfilVazio &e) {
                    Utils::printColor(Foreground::f_red, e.what());
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 17: // Listar transacoes
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "------------ LISTAR TRANSACOES ------------");
                std::cout << "CONTA, TIPO (receita ou despesa)" << std::endl;

                std::cin >> conta >> tipo;

                try {
                    gc.listarTransacao(conta, tipo);
                }
                catch (ctrexcp::ContaNaoEncontrada &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Conta: " << e.getNome()
                    << std::endl;
                }
                catch (trsexcp::TipoTransacaoInvalido &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Tipo: " << e.getTipo()
                    << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;
            case 18: // Sair
                break;
        }
        break;
    }

    Utils::limparConsole();

    return 0;
}

void printMenu() {
    Utils::printColor(Efeitos::inverse, "------------------- MENU ------------------");
    std::cout << "0 - Imprimir menu\n"
              << "1 - Adicionar carteira\n"
              << "2 - Adicionar carteira bancária\n"
              << "3 - Adicionar receita\n"
              << "4 - Adicionar despesa\n"
              << "5 - Adicionar despesa cartao de credito\n"
              << "6 - Adicionar transferencia\n"
              << "7 - Adicionar cartao de credito\n"
              << "8 - Remover carteira\n"
              << "9 - Remover conta\n"
              << "10 - Remover receita\n"
              << "11 - Remover despesa\n"
              << "12 - Remover despesa cartao de credito\n"
              << "13 - Remover transferencia\n"
              << "14 - Remover cartao de credito\n"
              << "15 - Pagar fatura de um cartão\n"
              << "16 - Listar carteiras\n"
              << "17 - Listas transacoes\n"
              << "18 - Sair\n";
}

void printMensagem() {
    Utils::printColor(Efeitos::underline, "Retornar ao menu ou sair!");
    std::cout << "0 - Imprimir menu\n"
              << "18 - Sair\n";
}
