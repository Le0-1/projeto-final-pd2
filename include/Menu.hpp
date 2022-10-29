#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <string>
#include <vector>

#define DEFAULT_VALUE 0
#define STANDARD_POSITION 0
#define MENU_HEIGHT 1
#define MENU_WIDTH COLS
#define EMPTY_SPACE 1
#define FULL_LINE -1
#define COLOR_BLACK_CYAN 1

class Menu {
    private:
    WINDOW *_window;
    std::vector<std::string> _names;
    int _current_position = STANDARD_POSITION;

    WINDOW *get_window();
    std::vector<std::string> get_names();
    void update_menu();
    void print_text(WINDOW *window, std::string text, int color_pair);

    public:
    Menu(std::vector<std::string> names);
    ~Menu();
    int get_current_position();
    void set_select_position(int position);
    void reload();
};

#endif