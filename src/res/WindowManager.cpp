#include "WindowManager.hpp"

WindowManager::WindowManager() { 
    start_config();
    set_menu_names();
    this->_menu = std::shared_ptr<Menu>(new Menu(get_menu_names()));
}

WindowManager::~WindowManager() {
    endwin();
}

std::shared_ptr<Menu> WindowManager::get_menu() {
    return this->_menu;
}

std::vector<std::string> WindowManager::get_menu_names() {
    return this->_menu_names;
}

void WindowManager::set_menu_names() {
    std::vector<std::string> names;
    names.push_back("Conta");
    names.push_back("Cartao");
    names.push_back("Transacao");

    this->_menu_names = names;
}

void WindowManager::start_config() {
    initscr();
    raw();
    noecho();
    use_default_colors();
    start_color();
    curs_set(0);
    refresh();
}

void WindowManager::start() {

    if (!has_colors()) {
        endwin();
        std::cout << "Terminal does not support colors" << std::endl;
        exit(1);
    }

    char ch = '\0';
    while (ch != 'p') {
        ch = getch();

        switch (ch) {
            case '1':
                get_menu()->set_select_position(0);
                break;
            case '2':
                get_menu()->set_select_position(1);
                break;
            case '3':
                get_menu()->set_select_position(2);
                break;
        }
    }
}
