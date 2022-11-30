#include "doctest.h"
#include "Carteira.hpp"

TEST_CASE("Teste Construtor Carteira - Exceção Saldo Negativo"){
    CHECK_THROWS_AS(Carteira novaCarteira("nome", -10), SaldoInvalido);
}

TEST_CASE("Teste getSaldoAtual") {
    Carteira novaCarteira("nome", 1);
    Transacao deposito1(100, "data", "categoria");
    Transacao deposito2(1000, "data", "categoria");
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
    CHECK_THROWS_AS(novaCarteira.setSaldoAtual(-10), SaldoInvalido);
}