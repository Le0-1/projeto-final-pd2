#include "Menu.hpp"

Menu::Menu(std::vector<std::string> names) {
    this->_names = names;
    this->_window = newwin(
        MENU_HEIGHT,
        MENU_WIDTH,
        STANDARD_POSITION,
        STANDARD_POSITION
    );

    init_pair(COLOR_BLACK_CYAN, COLOR_BLACK, COLOR_CYAN);
    set_select_position(STANDARD_POSITION);
    reload();
}

Menu::~Menu() {
    delwin(this->_window);
}

void Menu::reload() {
    set_select_position(get_current_position());
}

WINDOW *Menu::get_window() {
    return this->_window;
}

std::vector<std::string> Menu::get_names(){
    return this->_names;
}

int Menu::get_current_position() {
    return this->_current_position;
}

void Menu::set_select_position(int position) {
    this->_current_position = position;
    update_menu();
}

void Menu::print_text(WINDOW *window, std::string text, int color_pair) {
    std::string str = " " + text;
    wattron(window, color_pair);
    wprintw(window, "%s", str.c_str());
    wattroff(window, color_pair);
}

void Menu::update_menu() {
    
    int index = 0;
    int print_position = 0;
    
    for (std::string name : get_names()) {
        wmove(get_window(), STANDARD_POSITION, print_position);

        if (index == get_current_position()) {
            print_text(get_window(), name, COLOR_PAIR(COLOR_BLACK_CYAN));
        } else {
            print_text(get_window(), name, A_REVERSE);
        }

        print_position += name.length() + EMPTY_SPACE;
        index++;
    }

    wmove(get_window(), print_position, STANDARD_POSITION);
    wchgat(get_window(), FULL_LINE, A_REVERSE, DEFAULT_VALUE, NULL);
    wrefresh(get_window());
}