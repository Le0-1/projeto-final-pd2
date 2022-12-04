#ifndef BARRICADA_H
#define BARRICADA_H

#include "CartaoDeCreditoExcp.hpp"
#include "TransferenciaExcp.hpp"

#include <iostream>
#include <limits>
#include <regex>

class Barricada {
    private:
        static const std::string numero_cc_valido;
        static const std::string CVV_valido;
        static const std::string fechamento_valido;
        static const std::string data_valida;

    public:
        static void validar_saldo(double &saldo);

        static void validar_input(unsigned &input);

        static void validar_transacao(double &valor_transacao);

        static void validar_id(unsigned &id);

        static void validar_limite_cartao(double &limite);

        static bool validar_cartao(std::string& numero, std::string& CVV,
                                   std::string& fechamento);
        
        static bool validar_transferencia(std::string& data, std::string& origem,
                                          std::string& destino);
};

#endif