#ifndef GUIA_H
#define GUIA_H

#define VALOR_PADRAO 0
#define POSICAO_INICIAL 0
#define ALTURA_GUIA 1
#define LAGURA_GUIA COLS
#define ESPACO_VAZIO 1
#define LINHA_COMPLETA -1

#define PAR_COR_PRETO_CIANO 1
#define PAR_COR_VERDE 2
#define PAR_COR_VERMELHO 3

#include <ncurses.h>
#include <string>
#include <vector>

class Guia {
    private:
        WINDOW *_janela;
        std::vector<std::string> _nomes;
        int _posicao_atual;

        WINDOW *getJanela();

        std::vector<std::string> getNomes();

        void atualizarMenu();

        void imprimirTexto(WINDOW *janela, std::string texto, int par_cor);

    public:
        Guia(std::vector<std::string> nomes);

        ~Guia();

        int getPosicaoAtual();

        void setPosicaoSelecionada(int posicao);

        void recarregar();
};

#endif