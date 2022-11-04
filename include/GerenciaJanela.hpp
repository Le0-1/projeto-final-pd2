#ifndef GERENCIA_JANELE_H
#define GERENCIA_JANELE_H

#include "Guia.hpp"

#include <ncurses.h>
#include <memory>
#include <iostream>
#include <list>

class GerenciaJanela {
    private:
        std::shared_ptr<Guia> _guia;
        std::vector<std::string> _guia_nomes;

        std::shared_ptr<Guia> getGuia();

        void iniciarConfig();

        std::vector<std::string> getGuiaNomes();
        
        void setGuiaNomes();

    public:
        GerenciaJanela();

        ~GerenciaJanela();

        void iniciar();
};

#endif