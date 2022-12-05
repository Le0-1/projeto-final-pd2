#include "doctest.h"
#include "CarteiraBancaria.hpp"

TEST_CASE("Teste Construtor CarteiraBancaria - Caso Base"){
    CarteiraBancaria novaCarteiraBancaria("nome", 100);
    CHECK(novaCarteiraBancaria.getSaldoAtual() == 100);
}

TEST_CASE("Teste adicionarCartao - Caso Base") {
    CarteiraBancaria novaCarteiraBancaria("carteira_bancaria", 1000);
    CartaoDeCredito novoCartao("cartao", "101010101010101", "001", "10/11/1999", 1000);
    novaCarteiraBancaria.adicionarCartao(novoCartao);
    CHECK(novaCarteiraBancaria.getCartoes().size() != 0);
}

TEST_CASE("Teste removerCartao - Caso Base") {
    CarteiraBancaria novaCarteiraBancaria("carteira_bancaria", 1000);
    CartaoDeCredito novoCartao("cartao", "101010101010101", "001", "10/11/1999", 1000);
    novaCarteiraBancaria.removerCartao("cartao");
    CHECK(novaCarteiraBancaria.getCartoes().size() == 0);
}

TEST_CASE("Teste getCartaoDeCredito - Caso Base") {
    CarteiraBancaria novaCarteiraBancaria("carteira_bancaria", 1000);
    CartaoDeCredito novoCartao("cartao", "101010101010101", "001", "10/11/1999", 1000);
    CHECK(novaCarteiraBancaria.getCartaoDeCredito("cartao")->getNome() == "cartao");
}


