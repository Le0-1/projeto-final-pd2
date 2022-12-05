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

TEST_CASE("Teste adicionarConta - Exceção Conta Já Existente") {
    GerenciaConta gerente;
    gerente.adicionarConta("conta", 100);
    CHECK_THROWS_AS(gerente.adicionarConta("conta", 101), ctrexcp::ContaJaExiste);
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
    gerente.adicionarReceita("conta", 50, "10/10/2022", "categoria");
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
    auto it = gerente.getConta("Conta")->getTransacoes().rbegin();
    gerente.removerReceita("conta", it->second->getID());
    CHECK(gerente.getConta("conta")->getSaldoAtual() == 150);
}

TEST_CASE("Teste removerDespesa - Caso Base") {
    GerenciaConta gerente;
    gerente.adicionarConta("conta", 100);
    gerente.adicionarDespesa("conta", 50, "10/10/2022", "categoria");
    gerente.adicionarDespesa("conta", 50, "11/10/2022", "categoria");
    auto it = gerente.getConta("Conta")->getTransacoes().rbegin();
    gerente.removerDespesa("conta", it->second->getID());
    CHECK(gerente.getConta("conta")->getSaldoAtual() == 50);
}

TEST_CASE("Teste adicionarTransferencia - Caso Base") {
    GerenciaConta gerente;
    gerente.adicionarConta("conta", 1000);
    gerente.adicionarConta("conta_2", 1000);
    gerente.adicionarTransferencia(100, "10/10/2022", "categoria", "conta", "conta_2");
    CHECK(gerente.getConta("conta_2")->getSaldoAtual() == 1100);
}

TEST_CASE("Teste removerTransferencia - Caso Base") {
    GerenciaConta gerente;
    gerente.adicionarConta("conta", 1000);
    gerente.adicionarConta("conta_2", 1000);
    gerente.adicionarTransferencia(100, "10/10/2022", "categoria", "conta", "conta_2");
    gerente.adicionarTransferencia(100, "11/10/2022", "categoria", "conta", "conta_2");
    auto it = gerente.getConta("Conta")->getTransacoes().rbegin();
    gerente.removerTransferencia("conta", it->second->getID());
    CHECK(gerente.getConta("conta_2")->getSaldoAtual() == 1100);
}


