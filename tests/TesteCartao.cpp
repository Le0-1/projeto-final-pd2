
#include "doctest.h"
#include "CartaoDeCredito.hpp"

TEST_CASE("Teste alterarLimiteCartao - Casos Base"){
    CartaoDeCredito cartao("nome", "numero", "CVV", "fechamento", 1);
    cartao.alterarLimiteCartao(1000);
    CHECK(cartao.get_limite_cartao() == 1000);
}

TEST_CASE("Teste alterarLimiteCartao - Casos Gerais"){
    CartaoDeCredito cartao("nome", "numero", "CVV", "fechamento", 1);
    cartao.alterarLimiteCartao(460327);
    CHECK(cartao.get_limite_cartao() == 460327);
}

TEST_CASE("Teste alterarLimiteCartao - Casos Excepcionais"){
    CartaoDeCredito cartao("nome", "numero", "CVV", "fechamento", 1);
    CHECK_THROWS_AS(cartao.alterarLimiteCartao(-100), ExcecaoEntradaNegativa);
}




