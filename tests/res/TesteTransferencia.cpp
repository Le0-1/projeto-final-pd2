#include "doctest.h"
#include "Carteira.hpp"
#include "Transferencia.hpp"
#include "TransferenciaExcp.hpp"

TEST_CASE("Teste alterarDestino - Caso Base"){
    Carteira novaCarteiraA("carteiraA", 1000), novaCarteiraB("carteiraB", 1000), novaCarteiraC("carteiraC", 1000);
    Transferencia novaTransferencia(100, "11/11/2022", "categoria", "carteiraA", "carteiraB");
    novaTransferencia.alterarDestino("carteiraC");
    CHECK(novaTransferencia.getDestino() == "carteiraC");
}

TEST_CASE("Teste alterarOrigem - Caso Base"){
    Transferencia novaTransferencia(100, "11/11/2022", "categoria", "origem", "destino");
    novaTransferencia.alterarOrigem("nova_origem");
    CHECK(novaTransferencia.getOrigem() == "nova_origem");
}

TEST_CASE("Teste Construtor de Transferência - Exceção Data Invalida"){
    CHECK_THROWS_AS(Transferencia novaTransferencia(100, "data_invalida", "categoria", 
        "origem", "destino"), trfexcp::DataInvalida);
}

//Exceção DestinoInvalido/Origem Invalida ainda a ser implementada. 
//Passar um destino/origem que não existe, ou passar origem e destino iguais.

TEST_CASE("Teste Construtor de Transferência - Exceção Destino Invalido"){
    Carteira novaCarteiraA("carteiraA", 1000), novaCarteiraB("carteiraB", 1000);
    CHECK_THROWS_AS(Transferencia novaTransferencia(100, "11/11/2022", "categoria", "carteiraA", 
        "carteiraC"), trfexcp::DestinoInvalido);
}

TEST_CASE("Teste Construtor de Transferência - Exceção Destino Invalido, Destino = Origem"){
    Carteira novaCarteiraA("carteiraA", 1000), novaCarteiraB("carteiraB", 1000);
    CHECK_THROWS_AS(Transferencia novaTransferencia(100, "11/11/2022", "categoria", "carteiraA", 
        "carteiraA"), trfexcp::DestinoInvalido);
}

TEST_CASE("Teste Construtor de Transferência - Exceção Origem Invalida"){
    Carteira novaCarteiraA("carteiraA", 1000), novaCarteiraB("carteiraB", 1000);
    CHECK_THROWS_AS(Transferencia novaTransferencia(100, "11/11/2022", "categoria", "carteiraC", 
        "carteiraA"), trfexcp::OrigemInvalida);
}

//Exceção SaldoInsuficiente ainda a ser implementada.
//Passar um valor de transferencia superior ao saldo da conta origem.

TEST_CASE("Teste Construtor de Transferência - Exceção Saldo Insuficiente"){
    Carteira novaCarteiraA("carteiraA", 100), novaCarteiraB("carteiraB", 100);
    CHECK_THROWS_AS(Transferencia novaTransferencia(2000, "11/11/2022", "categoria", "carteiraA", 
        "carteiraB"), trfexcp::SaldoInsuficiente);
}

//Exceção ValorInvalido ainda a ser implementada.
//Tentar transferir um valor invalido. 

TEST_CASE("Teste Construtor de Transferência - Exceção Valor Invalido"){
    Carteira novaCarteiraA("carteiraA", 100), novaCarteiraB("carteiraB", 100);
    CHECK_THROWS_AS(Transferencia novaTransferencia(-100, "11/11/2022", "categoria", "carteiraA", 
        "carteiraB"), trfexcp::ValorInvalido);
}

