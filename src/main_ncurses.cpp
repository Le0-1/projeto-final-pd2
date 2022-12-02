#include <cstdlib>
#include <ncurses.h>
#include <string>
#include <vector>
#include <menu.h>
#include <form.h>

#define KEY_REGISTER KEY_F(1)
#define KEY_STOP KEY_F(2)
#define KEY_KILL KEY_F(5)
#define ENTER '\n'

int main(int argc, char ** argv) {

    std::vector<const char*> opcoes = {"Adicionar carteira", 
                                       "Remover carteira",
                                       "Adicionar conta",
                                       "Remover conta",
                                       "Adicionar receita",
                                       "Remover receita",
                                       "Adicionar despesa",
                                       "Remover despesa",
                                       "Adicionar despesa cartao de credito",
                                       "Remover despesa cartao de credito",
                                       "Adicionar transferencia",
                                       "Remover transferencia"};

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    int xMax, yMax;

    getmaxyx(stdscr, yMax, xMax);

    int menuHeight = yMax * 0.6,
        menuWidth = xMax * 0.37,
        menuStart_y = 0,
        menuStart_x = 0;
    
    int outputHeight = yMax,
        outputWidth = xMax * 0.62,
        outputStart_y = 0,
        outputStart_x = menuWidth + xMax * 0.01;

    int inputHeight = yMax - menuHeight, 
        inputWidth = menuWidth,
        inputStart_y = menuHeight + yMax * 0.01,
        inputStart_x = 0;
    
    WINDOW* menuWindow = newwin(menuHeight, menuWidth, menuStart_y, menuStart_x);
    refresh();
    box(menuWindow, 0, 0);
    mvwprintw(menuWindow, 0, 2, " MENU ");
    wrefresh(menuWindow);
    
    WINDOW* outputWindow = newwin(outputHeight, outputWidth, outputStart_y, outputStart_x);
    refresh();
    box(outputWindow, 0, 0);
    mvwprintw(outputWindow, 0, 2, " OUTPUT ");
    wrefresh(outputWindow);

    WINDOW* subOutputWindow = derwin(outputWindow, outputHeight * 0.96, outputWidth * 0.96 , 1, 2);
    refresh();
    wrefresh(subOutputWindow);
    scrollok(subOutputWindow, true);
    
    WINDOW* inputWindow = newwin(inputHeight, inputWidth, inputStart_y, inputStart_x);
    refresh();
    box(inputWindow, 0, 0);
    mvwprintw(inputWindow, 0, 2, " INPUT ");
    wrefresh(inputWindow);

    MENU *menu;
    int n_opcoes = opcoes.size();
    ITEM **itens = (ITEM **)calloc(n_opcoes, sizeof(ITEM *));

    for (int i = 0; i < n_opcoes; ++i) {
        itens[i] = new_item(opcoes[i], "");
    }

    menu = new_menu((ITEM **)itens);
    keypad(menuWindow, true);

    set_menu_win(menu, menuWindow);
    set_menu_sub(menu, derwin(menuWindow, n_opcoes, menuWidth*0.95, 2, 1));
    set_menu_mark(menu, " * ");

    post_menu(menu);
    wrefresh(menuWindow);

    int c;
    while((c = wgetch(menuWindow)) != KEY_KILL) {
        switch (c) {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;

            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;

            case ENTER:
                const char* item = item_name(current_item(menu));
                wprintw(subOutputWindow, "%s\n", item);
                wrefresh(subOutputWindow);

                if (item == opcoes[0]) {
                    wprintw(subOutputWindow, "Item 0\n");
                    wrefresh(subOutputWindow);
                }

                break;
        }
        wrefresh(menuWindow);
    }

    unpost_menu(menu);
    free_menu(menu);

    for (int i = 0; i < n_opcoes; i++) {
        free_item(itens[i]);
    }

    endwin();
}

