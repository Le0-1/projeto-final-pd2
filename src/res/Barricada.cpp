#include "Barricada.hpp"

const std::string Barricada::numero_cc_valido = "^[0-9]{16}$";
const std::string Barricada::CVV_valido = "^[0-9]{3}$";
const std::string Barricada::fechamento_valido = "^(([0]?[1-9])|([1-2][0-9])|(3[01]))$";
const std::string Barricada::data_valida = "^(?:(?:31(\\/|-|\\.)(?:0?[13578]|1[02]))\\1|"
                                       "(?:(?:29|30)(\\/|-|\\.)(?:0?[13-9]|1[0-2])\\2))"
                                       "(?:(?:1[6-9]|[2-9]\\d)?\\d{2})$|^(?:29(\\/|-|\\.)"
                                       "0?2\\3(?:(?:(?:1[6-9]|[2-9]\\d)?(?:0[48]|[2468]"
                                       "[048]|[13579][26])|(?:(?:16|[2468][048]|[3579][26])"
                                       "00))))$|^(?:0?[1-9]|1\\d|2[0-8])(\\/|-|\\.)(?:(?:0?"
                                       "[1-9])|(?:1[0-2]))\\4(?:(?:1[6-9]|[2-9]\\d)?\\d{2})$";

void Barricada::validar_saldo(double &saldo) {

    while (std::cin.fail() || saldo < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida, coloque um valor positivo: ";
        std::cin >> saldo;
    }

}

void Barricada::validar_input(unsigned &input) {

    /*entre 0 e 16 pq é o numero de opções do menu*/
    while (std::cin.fail() || input < 0 || input > 17) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida, coloque uma opção do menu: ";
        std::cin >> input;
    }

}

void Barricada::validar_transacao(double &valor_transacao) {

    while (std::cin.fail() || valor_transacao <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Entrada Inválida. Coloque um valor positivo: ";
        std::cin >> valor_transacao;
    }
}

void Barricada::validar_id(unsigned &id) {

    while (std::cin.fail() || id < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida, coloque um ID : ";
        std::cin >> id;
    }

}

void Barricada::validar_limite_cartao(double &limite_cartao) {

    while (std::cin.fail() || limite_cartao <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida, coloque um limite positivo : ";
        std::cin >> limite_cartao;
    }
}

bool Barricada::validar_cartao(std::string& numero, std::string& CVV,
                               std::string& fechamento) {
                                
    if (std::regex_match(numero, std::regex(numero_cc_valido))) {
        if (std::regex_match(CVV, std::regex(CVV_valido))) {
            if(std::regex_match(fechamento, std::regex(fechamento_valido))) {
                return true;
            } else {
                throw cdcexcp::FechamentoInvalido(fechamento);
            }
        } else {
            throw cdcexcp::CVVInvalido(CVV);
        }
    } else {
        throw cdcexcp::NumeroInvalido(numero);
    }
    return false;
}

bool Barricada::validar_transferencia(std::string& data, std::string& origem,
                                      std::string& destino) {

    if (origem == destino) {
        throw trfexcp::TransferenciaInvalida(origem);
    } else if (std::regex_match(data, std::regex(data_valida))) {
        return true;
    } else {
        throw trfexcp::DataInvalida(data);
    }
    return false;
}