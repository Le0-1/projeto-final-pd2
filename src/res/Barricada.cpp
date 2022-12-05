#include "Barricada.hpp"
#include "Utils.hpp"

#include <iomanip>
#include <ctime>
#include <sstream>

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

    /*entre 0 e 18 pq é o numero de opções do menu*/
    while (std::cin.fail() || input < 0 || input > 18) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida. Coloque uma opção do menu: ";
        std::cin >> input;
    }

}

void Barricada::validar_transacao(double &valor_transacao) {

    while (std::cin.fail() || valor_transacao <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Entrada inválida. Coloque um valor positivo: ";
        std::cin >> valor_transacao;
    }
}

void Barricada::validar_id(unsigned &id) {

    while (std::cin.fail() || id < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida. Coloque um ID: ";
        std::cin >> id;
    }

}

void Barricada::validar_limite_cartao(double &limite_cartao) {

    while (std::cin.fail() || limite_cartao <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida. Coloque um limite positivo: ";
        std::cin >> limite_cartao;
    }
}

bool Barricada::validar_cartao(std::string& numero, std::string& CVV,
                               std::string& fechamento) {
                                
    if (!std::regex_match(numero, std::regex(numero_cc_valido))) {
        throw cdcexcp::NumeroInvalido(numero);
    }
    if (!std::regex_match(CVV, std::regex(CVV_valido))) {
        throw cdcexcp::CVVInvalido(CVV);
    }
    if (!std::regex_match(fechamento, std::regex(fechamento_valido))) {
        throw cdcexcp::FechamentoInvalido(fechamento);
    }

    return true;
}

bool Barricada::validar_transferencia(std::string& data, std::string& origem,
                                      std::string& destino) {

    if (origem == destino) {
        throw trfexcp::TransferenciaInvalida(origem);
    }
    if (!std::regex_match(data, std::regex(data_valida))) {
        throw trsexcp::DataInvalida(data);
    }

    return true;
}

bool Barricada::validar_data(std::string& data) {

    if(std::regex_match(data, std::regex(data_valida))) {
        return true;
    }
    else {
        throw trsexcp::DataInvalida(data);
    }
    return false;
}

void Barricada::selecionarData(std::string &data) {
    Utils::printColorNoLine(Efeitos::bold_bright, "DESEJA COLOCAR A DATA DE HOJE? [s/n]: ");
    char resposta;
    std::cin >> resposta;

    if (resposta == 's' || resposta == 'S') {
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%d/%m/%Y");
        data = oss.str();
        Utils::printColorNoLine(Efeitos::bold_bright, "A DATA DE HOJE É: ");
        std::cout << data << std::endl;
    }
    else {
        Utils::printColorNoLine(Efeitos::bold_bright, "DIGITE A DATA DESEJADA: ");
        std::cin >> data;
    }

}
