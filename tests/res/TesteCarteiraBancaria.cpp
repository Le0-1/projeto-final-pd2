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

TEST_CASE("Teste getCartaoDeCredito - Exceção Cartão Não Encontrado") {
    CarteiraBancaria novaCarteiraBancaria("carteira_bancaria", 1000);
    CartaoDeCredito novoCartao("cartao", "101010101010101", "001", "10/11/1999", 1000);
    CHECK_THROWS_AS(novaCarteiraBancaria.getCartaoDeCredito("cartao_inexistente"), cdcexcp::CartaoNaoEncontrado);
}

TEST_CASE("Teste pagarFatura- Caso Base") {
    CarteiraBancaria novaCarteiraBancaria("carteira_bancaria", 1000);
    CartaoDeCredito novoCartao("cartao", "101010101010101", "001", "10/11/1999", 1000);
    novaCarteiraBancaria.adicionarCartao(novoCartao);
    novoCartao.adicionarDespesa(200, "10/11/1999", "açougue");
    novoCartao.adicionarDespesa(100, "10/11/1999", "supermercado");
    novoCartao.adicionarDespesa(150, "10/11/1999", "padaria");
    novaCarteiraBancaria.pagarFatura("cartao");
    CHECK(novaCarteiraBancaria.getSaldoAtual() == 550);
}

TEST_CASE("Teste adicionarCartao - Exceção Cartão Já Existente") {
    CarteiraBancaria novaCarteiraBancaria("carteira_bancaria", 1000);
    CartaoDeCredito novoCartao("cartao", "101010101010101", "001", "10/11/1999", 1000);
    novaCarteiraBancaria.adicionarCartao(novoCartao);
    CHECK_THROWS_AS(novaCarteiraBancaria.adicionarCartao(novoCartao), cdcexcp::CartaoJaExiste);
}

TEST_CASE("Teste adicionarCartao - Exceção Número Invalido") {
    CarteiraBancaria novaCarteiraBancaria("carteira_bancaria", 1000);
    CartaoDeCredito cartao("nome", "0", "001", "10/11/1999", 100);
    CHECK_THROWS_AS(novaCarteiraBancaria.adicionarCartao(cartao), cdcexcp::NumeroInvalido);
}

TEST_CASE("Teste adicionarCartao - Exceção CVV Invalido") {
    CarteiraBancaria novaCarteiraBancaria("carteira_bancaria", 1000);
    CartaoDeCredito cartao("nome", "101010101010101", "00001", "10/11/1999", 100);
    CHECK_THROWS_AS(novaCarteiraBancaria.adicionarCartao(cartao), cdcexcp::CVVInvalido);
}

TEST_CASE("Teste adicionarCartao - Exceção Fechamento Invalido") {
    CarteiraBancaria novaCarteiraBancaria("carteira_bancaria", 1000);
    CartaoDeCredito cartao("nome", "101010101010101", "001", "40/12/1999", 100);
    CHECK_THROWS_AS(novaCarteiraBancaria.adicionarCartao(cartao), cdcexcp::FechamentoInvalido);
}

TEST_CASE("Teste adicionarCartao - Caso Base") {
    CarteiraBancaria novaCarteiraBancaria("carteira_bancaria", 1000);
    CartaoDeCredito novoCartao("cartao", "101010101010101", "001", "10/11/1999", 1000);
    novaCarteiraBancaria.adicionarCartao(novoCartao);
    CHECK(novaCarteiraBancaria.getCartoes().size() != 0);
}