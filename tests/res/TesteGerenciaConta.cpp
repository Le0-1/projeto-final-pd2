#include "doctest.h"
#include "GerenciaConta.hpp"

TEST_CASE("Teste adicionarCarteira - Caso Base") {
    GerenciaConta gerente;
    gerente.adicionarCarteira("carteira", 100);
    CHECK(gerente.getContas().size() != 0);
}

TEST_CASE("Teste adicionarConta - Caso Base") {
    GerenciaConta gerente;
    gerente.adicionarConta("conta", 100);
    CHECK(gerente.getContas().size() != 0);
}

TEST_CASE("Teste removerConta - Caso Base") {
    GerenciaConta gerente;
    gerente.adicionarConta("conta", 100);
    gerente.removerConta("conta");
    CHECK(gerente.getContas().size() == 0);
}

TEST_CASE("Teste adicionarReceita - Caso Base") {
    GerenciaConta gerente;
    gerente.adicionarConta("conta", 100);
    gerente.adicionarDespesa("conta", 50, "10/10/2022", "categoria");
    CHECK(gerente.getConta("conta")->getSaldoAtual() == 150);
}

TEST_CASE("Teste adicionarDespesa - Caso Base") {
    GerenciaConta gerente;
    gerente.adicionarConta("conta", 100);
    gerente.adicionarDespesa("conta", 50, "10/10/2022", "categoria");
    CHECK(gerente.getConta("conta")->getSaldoAtual() == 50);
}

TEST_CASE("Teste removerReceita - Caso Base") {
    GerenciaConta gerente;
    gerente.adicionarConta("conta", 100);
    gerente.adicionarReceita("conta", 50, "10/10/2022", "categoria");
    gerente.adicionarReceita("conta", 50, "11/10/2022", "categoria");
    gerente.removerReceita("conta", 1);
    CHECK(gerente.getConta("conta")->getSaldoAtual() == 150);
}

TEST_CASE("Teste removerDespesa - Caso Base") {
    GerenciaConta gerente;
    gerente.adicionarConta("conta", 100);
    gerente.adicionarDespesa("conta", 50, "10/10/2022", "categoria");
    gerente.adicionarDespesa("conta", 50, "11/10/2022", "categoria");
    gerente.removerDespesa("conta", 1);
    CHECK(gerente.getConta("conta")->getSaldoAtual() == 50);
}
