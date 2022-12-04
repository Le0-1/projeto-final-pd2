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
                std::cout << "NOME, SALDO INICIAL" << std::endl;

                std::cin >> nome >> saldo_inicial;

                /*Barricada que verifica o valor do saldo*/
                Barricada::validar_saldo(saldo_inicial);

                try {
                    gc.adicionarCarteira(nome, saldo_inicial);
                    std::cout << "Carteira criada" << std::endl;
                }

                catch (ctrexcp::ValorInvalido& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Carteira: " << e.getNome()
                    << "\t saldo: " << e.getValor()
                    << std::endl;
                }

                catch (ctrexcp::ContaJaExiste &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Nome: " << e.getNome()
                    << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 2: // Adicionar conta
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "--------------- NOVA CONTA ----------------");
                std::cout << "NOME, SALDO" << std::endl;

                std::cin >> nome >> saldo_inicial;

                /*Barricada que verifica o valor da transacao*/
                Barricada::validar_saldo(saldo_inicial);

                try {
                    gc.adicionarConta(nome, saldo_inicial);
                    std::cout << "Conta criada" << std::endl;
                }
                catch (ctrexcp::ValorInvalido& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Conta: " << e.getNome()
                    << "\t saldo: " << e.getValor()
                    << std::endl;
                }
                catch (ctrexcp::ContaJaExiste &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Nome: " << e.getNome()
                    << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 3: // Remover carteira
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, 
                                 "------------ REMOVER CARTEIRA -------------");
                std::cout << "NOME" << std::endl;

                std::cin >> nome;

                try {
                    gc.removerConta(nome);
                    std::cout << "Carteira removida" << std::endl;
                }

                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Carteira: " << e.getNome()
                    << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 4: // Remover conta
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "--------------- REMOVER CONTA -------------");
                std::cout << "NOME" << std::endl;
                std::cin >> nome;

                try {
                    gc.removerConta(nome);
                    std::cout << "Conta removida" << std::endl;
                }

                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Conta: " << e.getNome()
                    << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 5: // Adicionar receita
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "----------- ADICIONAR RECEITA -------------");
                std::cout << "CONTA, VALOR, DATA, CATEGORIA" << std::endl;

                std::cin >> conta >> valor_transacao;

                /*Barricada que verifica o valor da transacao*/
                Barricada::validar_transacao(valor_transacao);
                Barricada::selecionarData(data);
                std::cin >> categoria;

                try {
                    gc.adicionarReceita(conta, valor_transacao, data, categoria);
                    std::cout << "Receita adicionada" << std::endl;
                }
                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Conta: " << e.getNome()
                    << std::endl;
                }
                catch (ctrexcp::ValorInvalido &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Valor: " << e.getValor()
                    << std::endl;
                }
                catch (ctrexcp::ContaNaoPermiteCartao &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Conta: " << e.getNomeConta()
                    << "\t Subtipo: " << e.getSubtipoConta()
                    << std::endl;
                }
                catch (trsexcp::DataInvalida &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\tData: " << e.getData()
                    << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 6: // Adicionar despesa
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "------------ ADICIONAR DESPESA ------------");
                std::cout << "CONTA, VALOR, DATA, CATEGORIA" << std::endl;

                std::cin >> conta;
                std::cin >> valor_transacao;

                /*Barricada que verifica o valor da transacao*/
                Barricada::validar_transacao(valor_transacao);
                Barricada::selecionarData(data);
                std::cin >>  categoria;


                try {
                    gc.adicionarDespesa(conta, valor_transacao, data, categoria);
                    std::cout << "Despesa adicionada" << std::endl;
                }

                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Conta: " << e.getNome()
                    << std::endl;
                }

                catch (ctrexcp::ValorInvalido &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Valor: " << e.getValor()
                    << std::endl;
                }

                catch (ctrexcp::SaldoInsuficiente &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Diferença: " << e.getSaldo() - e.getDespesa()
                    << std::endl;
                } 
                catch (trsexcp::DataInvalida &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\tData: " << e.getData()
                    << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 7: // Adicionar despesa cartao de credito
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "--- ADICIONAR DESPESA CARTAO DE CREDITO ---");
                std::cout << "CONTA, CARTAO, DATA, CATEGORIA, VALOR" << std::endl;

                std::cin >> conta >> cartao;

                Barricada::selecionarData(data);

                std::cin >> categoria >> valor_transacao;

                /*Barricada que verifica o valor da transacao*/
                Barricada::validar_transacao(valor_transacao);

                try {
                    gc.adicionarDespesaCartao(conta, cartao, valor_transacao, data, categoria);
                    std::cout << "Despesa cartao de credito adicionada" << std::endl;
                }

                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Conta: " << e.getNome()
                    << std::endl;
                }

                catch (cdcexcp::CartaoNaoEncontrado& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Cartao: " << e.getNomeCartao()
                    << std::endl;
                }

                catch (cdcexcp::LimiteExcedido& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\n Limite restante do cartão " << e.getNomeCartao()
                    << " é: " << e.getLimiteCartao() - e.getSomaDespesasAtuais
                    << std::endl;
                }
                catch (trsexcp::DataInvalida &e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\tData: " << e.getData()
                    << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 8: // Adicionar transferencia
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "--------- ADICIONAR TRANSFERENCIA ---------");
                std::cout << "VALOR, DATA, CATEGORIA, ORIGEM, DESTINO" << std::endl;

                std::cin >> valor_transacao;

                /*Barricada que verifica o valor da transacao*/
                Barricada::validar_transacao(valor_transacao);

                Barricada::selecionarData(data);
                std::cin >> categoria >> origem >> destino;

                try {
                    gc.adicionarTransferencia(valor_transacao, data, categoria, origem, destino);
                    std::cout << "transferencia adicionada" << std::endl;
                }

                catch (trfexcp::TransferenciaInvalida& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Conta: " << e.getNomeConta()
                    << std::endl;
                }

                catch (ctrexcp::ValorInvalido& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    Utils::printColor(Foreground::f_red, ", transferência deixa saldo negativo");
                    std::cout << "Conta: " << e.getNome() 
                    << "\t saldo: " << e.getValor()
                    << "\t valor da transferência: " << valor_transacao
                    << std::endl;
                }

                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Conta: " << e.getNome()
                    << std::endl;
                } 

                catch (trfexcp::DataInvalida& e){
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Data: " << e.getData()
                    << std::endl;
                }

                Utils::printColor(corSeparador, separador);
                std::cout << std::endl;
                printMensagem();

                continue;

            case 9: // Remover receita
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

            case 10: // Remover despesa
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

            case 11: // Remover despesa cartao de credito
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

            case 12: // Remover transferencia
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

            case 13: // Adicionar cartao de credito
                Utils::printColor(corSeparador, separador);
                Utils::printColor(Efeitos::inverse, "------- ADICIONAR CARTAO DE CREDITO -------");
                std::cout << "CONTA, NOME, NUMERO, CVV, FECHAMENTO,\nLIMITE CARTAO" << std::endl;

                std::cin >> conta >> nome >> numero_cartao >> CVV >> fechamento >> limite_cartao;

                /*Barricada que irá verificar o valor do limite passado*/
                Barricada::validar_limite_cartao(limite_cartao);

                try {
                    gc.adicionarCartao(conta, nome, numero_cartao, CVV, fechamento, limite_cartao);
                    std::cout << "Cartao de credito criado" << std::endl;
                }

                catch (ctrexcp::ContaNaoEncontrada& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Conta: " << e.getNome()
                    << std::endl;
                }

                catch (cdcexcp::LimiteInvalido& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Limite digitado: " << e.getLimiteCartao()
                    << std::endl;
                }

                catch (cdcexcp::NumeroInvalido& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Número digitado: " << e.getNumero()
                    << std::endl;
                }

                catch (cdcexcp::CVVInvalido& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t CVV digitado: " << e.getCVV()
                    << std::endl;          
                              
                }

                catch (cdcexcp::FechamentoInvalido& e) {
                    Utils::printColorNoLine(Foreground::f_red, e.what());
                    std::cout << "\t Fechamento digitado: " << e.getFechamento()
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
