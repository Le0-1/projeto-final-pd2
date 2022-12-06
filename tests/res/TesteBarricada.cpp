#include "doctest.h"
#include "Barricada.hpp"

TEST_CASE("Barricada - NumeroInvalido") {
    CHECK_THROWS_AS(Barricada::validar_cartao("1234", "123", "12"), cdcexcp::NumeroInvalido);
}

TEST_CASE("Barricada - CVVInvalido") {
    CHECK_THROWS_AS(Barricada::validar_cartao("1234123412341234", "1", "12"), cdcexcp::CVVInvalido);
}

TEST_CASE("Barricada - FechamentoInvalido") {
    CHECK_THROWS_AS(Barricada::validar_cartao("1234123412341234", "123", "50"), cdcexcp::FechamentoInvalido);
}
