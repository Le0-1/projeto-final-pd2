#include "GerenciaJanela.hpp"

GerenciaJanela::GerenciaJanela() { 
    iniciarConfig();
    setGuiaNomes();
    setCores();
    this->_guia = std::shared_ptr<Guia>(new Guia(getGuiaNomes()));
    this->_janela = newwin(
        ALTURA_ABA,
        LAGURA_ABA,
        POSICAO_INICIAL_Y,
        POSICAO_INICIAL_X
    );
}

GerenciaJanela::~GerenciaJanela() {
    delwin(this->_janela);
    endwin();
}

std::shared_ptr<Guia> GerenciaJanela::getGuia() {
    return this->_guia;
}

std::vector<std::string> GerenciaJanela::getGuiaNomes() {
    return this->_guia_nomes;
}

void GerenciaJanela::setGuiaNomes() {
    std::vector<std::string> names;
    names.push_back("Conta");
    names.push_back("Cartao");
    names.push_back("Transacao");

    this->_guia_nomes = names;
}

void GerenciaJanela::setCores() {
    init_pair(PAR_COR_PRETO_CIANO, COR_PRETO, COR_CIANO);
    init_pair(PAR_COR_VERDE, COR_VERDE, COR_SISTEMA);
    init_pair(PAR_COR_VERMELHO, COR_VERMELHO, COR_SISTEMA);
}

void GerenciaJanela::iniciarConfig() {
    initscr();
    raw();
    noecho();
    use_default_colors();
    start_color();
    curs_set(0);
    refresh();
}

void GerenciaJanela::iniciar() {

    if (!has_colors()) {
        endwin();
        std::cout << "Terminal nao suporta cores" << std::endl;
        exit(1);
    }

    char ch = '\0';
    while (ch != 'p') {
        ch = getch();

        switch (ch) {
            case '1':
                getGuia()->setPosicaoSelecionada(0);
                break;
            case '2':
                getGuia()->setPosicaoSelecionada(1);
                break;
            case '3':
                getGuia()->setPosicaoSelecionada(2);
                break;
        }
    }
}
