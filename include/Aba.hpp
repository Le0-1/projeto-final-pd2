#ifndef ABA_H
#define ABA_H

#define POSICAO_ESCRITA 1

#include <ncurses.h>
#include <string>

class Aba {
    private:
        WINDOW *_janela;
        int _posicao_escrita_x;
        int _posicao_escrita_y;

        WINDOW *getJanela();

        int getPosicaoEscritaX();

        int getPosicaoEscritaY();

        void setPosicaoEscritaX(int posicao);

        void setPosicaoEscritaY(int posicao);

        void proximaPosicaoEscrita();

        void proximaPosicaoEscrita(int tamanho);

        void limparJanela();

        void imprimirTexto(std::string texto);

        void imprimirTexto(std::string texto, int par_cor);

        virtual void imprimirInfo() = 0;

    protected:
        void imprimir(std::string texto);

        void imprimir(std::string texto, int par_cor);

        void imprimirln(std::string texto);

        void imprimirln(std::string texto, int par_cor);

    public:
        Aba(WINDOW* janela);
        
        void mostrarInfo();
};

#endif