#ifndef GERENCIA_JANELE_H
#define GERENCIA_JANELE_H

#define POSICAO_INICIAL_X 0
#define POSICAO_INICIAL_Y 1
#define ALTURA_ABA LINES - 1
#define LAGURA_ABA COLS

#define COR_SISTEMA -1
#define COR_PRETO    0
#define COR_VERMELHO 1
#define COR_VERDE	 2
#define COR_AMARELO  3
#define COR_AZUL     4
#define COR_MAGENTA  5
#define COR_CIANO    6
#define COR_BRANCO   7

#define PAR_COR_PRETO_CIANO 1
#define PAR_COR_VERDE 2
#define PAR_COR_VERMELHO 3

#include "Guia.hpp"
#include "Aba.hpp"
#include "AbaConta.hpp"

#include <ncurses.h>
#include <memory>
#include <iostream>
#include <list>

class GerenciaJanela {
    private:
        WINDOW* _janela;
        std::shared_ptr<Guia> _guia;
        std::vector<std::string> _guia_nomes;
        std::vector<Aba*> _abas;

        std::shared_ptr<Guia> getGuia();

        void iniciarConfig();

        std::vector<std::string> getGuiaNomes();

        void setCores();
        
        void setGuiaNomes();

    public:
        GerenciaJanela();

        ~GerenciaJanela();

        void iniciar();
};

#endif