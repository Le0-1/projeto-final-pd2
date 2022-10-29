#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "Menu.hpp"

#include <ncurses.h>
#include <memory>
#include <iostream>
#include <list>

class WindowManager {
    private:
    std::shared_ptr<Menu> _menu;
    std::vector<std::string> _menu_names;

    std::shared_ptr<Menu> get_menu();
    void start_config();
    std::vector<std::string> get_menu_names();
    void set_menu_names();

    public:
    WindowManager();
    ~WindowManager();
    void start();
};

#endif