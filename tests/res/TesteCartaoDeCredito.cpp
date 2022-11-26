#include "doctest.h"
#include "CartaoDeCredito.hpp"

// Se forem criadas outras transacoes antes deste teste o ID nao sera igual a 2
TEST_CASE("Remover despesa") {
    CartaoDeCredito banco1("b1", "1234556781", "001", "10", 100);
    banco1.adicionarDespesa(10, "10/11/1999", "padaria");
    banco1.adicionarDespesa(15, "10/11/1999", "padaria");
    CHECK(banco1.removerDespesa(2) == true);
}

TEST_CASE("Criar cartao") {
    CartaoDeCredito banco1("b1", "1234556781", "001", "10", 100);
    CHECK(banco1.getLimite() == 100);
}

TEST_CASE("Alterar limite") {
    CartaoDeCredito banco1("b1", "1234556781", "001", "10", 100);
    banco1.alterarLimiteCartao(150);
    CHECK(banco1.getLimite() == 150);
}

TEST_CASE("Soma total do valor das despesas") {
    CartaoDeCredito banco1("b1", "1234556781", "001", "10", 100);
    banco1.adicionarDespesa(10, "10/11/1999", "padaria");
    banco1.adicionarDespesa(15, "10/11/1999", "padaria");
    banco1.adicionarDespesa(1.5, "10/11/1999", "padaria");
    CHECK(banco1.getTotalDespesas() == 26.5);
}

TEST_CASE("Excessao limite excedido") {
    CartaoDeCredito banco1("b1", "1234556781", "001", "10", 10);
    CHECK_THROWS_AS(banco1.adicionarDespesa(11, "10/11/1999", "padaria"), LimiteExcedido);
}
