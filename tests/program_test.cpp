#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Transacao.hpp"
#include "Carteira.hpp"

TEST_CASE("Teste da classe Transacao") {
    Transacao t1(150, "picanha", "19081991", "supermercado");
    Transacao t2(10, "biscoito", "19/02/1995", "supermercado");
    Transacao t3(5.70, "pao frances", "29/03/1991", "padaria");

    CHECK(t1.getCategoria() == "supermercado");
    CHECK(t2.getData() == "19/02/1995");
    CHECK(t3.getValor() == 5.70);
    CHECK(t3.getDescricao() == "pao frances");
    
    CHECK(t1.getID() == 1);
    CHECK(t2.getID() == 2);
    CHECK(t3.getID() == 3);
}

TEST_CASE("Teste da classe Carteira") {
    Carteira c1("banco papanamerico");
    Carteira c2(6.75, "banco do maicao", 6.75);
    
    CHECK(c2.getNome() == "banco do maicao");
    CHECK(c2.getSaldoAtual() == 6.75);
    CHECK(c1.getSaldoInicial() == 0);
          
    Transacao t4(10, "biscoito", "19/02/1995", "supermercado");
    Transacao t5(5.70, "pao frances", "29/03/1991", "padaria");
    Transacao t6(5.70, "pao frances", "29/03/1991", "padaria");
    
    c1.adicionarTransacao(t4);
    c1.adicionarTransacao(t5);
    c1.adicionarTransacao(t6);
    CHECK(c1.ultimasTransacoes(3).begin()->first == t4.getID());

    CHECK(c1.ultimasTransacoes(10).size() == 3);

    c1.removerTransacao(t4);
    c1.removerTransacao(t6);
    CHECK(c1.ultimasTransacoes(1).begin()->first == t5.getID());
    c1.removerTransacao(t5);
    CHECK(c1.ultimasTransacoes(1).empty() == true);
}


