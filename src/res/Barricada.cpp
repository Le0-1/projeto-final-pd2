#include "Barricada.hpp"
#include <limits>

void Barrier::Barricada::validar_saldo(double &saldo) {

    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida, coloque um valor positivo: ";
        std::cin >> saldo;
    }

}

void Barrier::Barricada::validar_input(unsigned &input) {

    /*entre 0 e 16 pq é o numero de opções do menu*/
    while (std::cin.fail() || input < 0 || input > 16) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida, coloque uma opção do menu: ";
        std::cin >> input;
    }

}

void Barrier::Barricada::validar_transacao(double &valor_transacao) {

    while (std::cin.fail() || valor_transacao <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Entrada Inválida. Coloque um valor positivo: ";
        std::cin >> valor_transacao;
    }
}

void Barrier::Barricada::validar_id(unsigned &id) {

    while (std::cin.fail() || id < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida, coloque um ID : ";
        std::cin >> id;
    }

}

void Barrier::Barricada::validar_limite_cartao(double &limite_cartao) {

    while (std::cin.fail() || limite_cartao <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida, coloque um limite positivo : ";
        std::cin >> limite_cartao;
    }
}

