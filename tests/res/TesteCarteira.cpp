#include "doctest.h"
#include "Carteira.hpp"
#include "Receita.hpp"
#include "Despesa.hpp"
#include "GerenciaContaExcp.hpp"

TEST_CASE("Teste Construtor Carteira - Exceção Saldo Negativo"){
    CHECK_THROWS_AS(Carteira novaCarteira("nome", -10), gcexcp::ValorInvalido);
}

TEST_CASE("Teste getSaldoAtual") {
    Carteira novaCarteira("nome", 1);
    
    std::shared_ptr<Receita> deposito1 = 
        std::make_shared<Receita>(novaCarteira.getNome(), 100, "data", "categoria");
    std::shared_ptr<Receita> deposito2 = 
        std::make_shared<Receita>(novaCarteira.getNome(), 1000, "data", "categoria");

    novaCarteira.adicionarTransacao(deposito1);
    novaCarteira.adicionarTransacao(deposito2);
    CHECK(novaCarteira.getSaldoAtual() == 1101);
}

TEST_CASE("Teste setSaldoAtual - Caso Base") {
    Carteira novaCarteira("nome", 1);
    novaCarteira.setSaldoAtual(100);
    CHECK(novaCarteira.getSaldoAtual() == 100);
}

TEST_CASE("Teste setSaldoAtual - Exceção Saldo Negativo") {
    Carteira novaCarteira("nome", 1);
    CHECK_THROWS_AS(novaCarteira.setSaldoAtual(-10), gcexcp::ValorInvalido);
}

TEST_CASE("Teste adicionarTransacao - Caso Base Receita") {
    Carteira novaCarteira("nome", 1000);
    Receita novaReceita("Conta", 100, "data", "receita");
    std::shared_ptr<Transacao> receita = std::make_shared<Transacao>(novaReceita);
    novaCarteira.adicionarTransacao(receita);
    CHECK(novaCarteira.getSaldoAtual() == 1100);
}

TEST_CASE("Teste adicionarTransacao - Caso Base Despesa") {
    Carteira novaCarteira("nome", 1000);
    Despesa novaDespesa(100, "data", "despesa", "conta");
    std::shared_ptr<Transacao> despesa = std::make_shared<Transacao>(novaDespesa);
    novaCarteira.adicionarTransacao(despesa);
    CHECK(novaCarteira.getSaldoAtual() == 900);
}

TEST_CASE("Teste adicionarTransacao - Excecao Despesa Superior ao Saldo") {
    Carteira novaCarteira("nome", 1000);
    Despesa novaDespesa(1100, "data", "despesa", "conta");
    std::shared_ptr<Transacao> despesa = std::make_shared<Transacao>(novaDespesa);
    CHECK_THROWS_AS(novaCarteira.adicionarTransacao(despesa), gcexcp::SaldoInsuficiente);
}

