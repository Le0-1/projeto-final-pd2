#include "Guia.hpp"

Guia::Guia(std::vector<std::string> nomes) {
    this->_nomes = nomes;
    this->_janela = newwin(
        ALTURA_GUIA,
        LAGURA_GUIA,
        POSICAO_INICIAL,
        POSICAO_INICIAL
    );

    init_pair(COR_PRETO_CIANO, COLOR_BLACK, COLOR_CYAN);
    setPosicaoSelecionda(POSICAO_INICIAL);
    recarregar();
}

Guia::~Guia() {
    delwin(this->_janela);
}

void Guia::recarregar() {
    setPosicaoSelecionda(getPosicaoAtual());
}

WINDOW *Guia::getJanela() {
    return this->_janela;
}

std::vector<std::string> Guia::getNomes(){
    return this->_nomes;
}

int Guia::getPosicaoAtual() {
    return this->_posicao_atual;
}

void Guia::setPosicaoSelecionda(int posicao) {
    this->_posicao_atual = posicao;
    atualizarMenu();
}

void Guia::imprimirTexto(WINDOW *janela, std::string texto, int par_cor) {
    std::string str = " " + texto;
    wattron(janela, par_cor);
    wprintw(janela, "%s", str.c_str());
    wattroff(janela, par_cor);
}

void Guia::atualizarMenu() {
    
    int indice = 0;
    int posicao_imprimir = 0;
    
    for (std::string nome : getNomes()) {
        wmove(getJanela(), POSICAO_INICIAL, posicao_imprimir);

        if (indice == getPosicaoAtual()) {
            imprimirTexto(getJanela(), nome, COLOR_PAIR(COR_PRETO_CIANO));
        } else {
            imprimirTexto(getJanela(), nome, A_REVERSE);
        }

        posicao_imprimir += nome.length() + ESPACO_VAZIO;
        indice++;
    }

    wmove(getJanela(), posicao_imprimir, POSICAO_INICIAL);
    wchgat(getJanela(), LINHA_COMPLETA, A_REVERSE, VALOR_PADRAO, NULL);
    wrefresh(getJanela());
}