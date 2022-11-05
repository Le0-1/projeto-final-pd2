#include "Aba.hpp"

Aba::Aba(WINDOW* janela) {
    this->_janela = janela;
    this->_posicao_escrita_x = POSICAO_ESCRITA;
    this->_posicao_escrita_y = POSICAO_ESCRITA;
}

WINDOW *Aba::getJanela() {
    return this->_janela;
}

int Aba::getPosicaoEscritaX() {
    return this->_posicao_escrita_x;
}

int Aba::getPosicaoEscritaY() {
    return this->_posicao_escrita_y;
}

void Aba::setPosicaoEscritaX(int posicao) {
    this->_posicao_escrita_x = posicao;
}

void Aba::setPosicaoEscritaY(int posicao) {
    this->_posicao_escrita_y = posicao;
}

void Aba::proximaPosicaoEscrita() {
    setPosicaoEscritaX(POSICAO_ESCRITA);
    setPosicaoEscritaY(getPosicaoEscritaY() + 1);
}

void Aba::proximaPosicaoEscrita(int tamanho) {
    setPosicaoEscritaX(getPosicaoEscritaX() + tamanho);
}

void Aba::limparJanela() {
    werase(getJanela());
}

void Aba::imprimirTexto(std::string texto) {
    wmove(getJanela(), getPosicaoEscritaY(), getPosicaoEscritaX());
    
    wprintw(getJanela(), "%s", texto.c_str());

    wrefresh(getJanela());
}

void Aba::imprimirTexto(std::string texto, int par_cor) {
    wmove(getJanela(), getPosicaoEscritaY(), getPosicaoEscritaX());

    wattron(getJanela(), COLOR_PAIR(par_cor));
    wprintw(getJanela(), "%s", texto.c_str());
    wattroff(getJanela(), COLOR_PAIR(par_cor));

    wrefresh(getJanela());
}

void Aba::imprimir(std::string texto) {
    imprimirTexto(texto);
    proximaPosicaoEscrita(texto.length());
}

void Aba::imprimir(std::string texto, int par_cor) {
    imprimirTexto(texto, par_cor);
    proximaPosicaoEscrita(texto.length());
}

void Aba::imprimirln(std::string texto) {
    imprimirTexto(texto);
    proximaPosicaoEscrita();
}

void Aba::imprimirln(std::string texto, int par_cor) {
    imprimirTexto(texto, par_cor);
    proximaPosicaoEscrita();
}

void Aba::mostrarInfo() {
    setPosicaoEscritaX(POSICAO_ESCRITA);
    setPosicaoEscritaY(POSICAO_ESCRITA);

    limparJanela();
    imprimirInfo();
}