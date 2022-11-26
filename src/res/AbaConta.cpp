#include "AbaConta.hpp"

AbaConta::AbaConta(WINDOW *janela) : Aba(janela) {
    this->_contas.push_back(new Carteira(0, "Itau", 200));
    this->_contas.push_back(new Carteira(0, "Bradesco", -500));
    this->_contas.push_back(new Carteira(0, "Santander", 0));
    this->_contas.push_back(new Carteira(0, "Bando do Brasil", -1200));
    this->_contas.push_back(new Carteira(0, "Nubank", 1700));
    this->_contas.push_back(new Carteira(0, "Banco Inter", 1132));
    this->_contas.push_back(new Carteira(0, "Caixa", 1234));
    this->_contas.push_back(new Carteira(0, "Neon", 563));
    this->_contas.push_back(new Carteira(0, "C6", -445));
}

std::vector<Carteira *> &AbaConta::get_contas() {
    return this->_contas;
}

void AbaConta::imprimirInfo() {
    for (Carteira *conta : get_contas()) {
        imprimirln("* " + conta->getNome());

        imprimir("Saldo: ");
        std::string saldo = std::to_string(conta->getSaldoAtual());

        if (conta->getSaldoAtual() > 0) {
            imprimirln("R$ " + saldo.substr(0, saldo.find(".") + 3), 2);
        } 
        else if (conta->getSaldoAtual() < 0) {
            imprimirln("R$ " + saldo.substr(0, saldo.find(".") + 3), 3);
        } 
        else {
            imprimirln("R$ " + saldo.substr(0, saldo.find(".") + 3));
        }

        imprimirln("___________________________________________________");
        imprimirln("");
    }
}