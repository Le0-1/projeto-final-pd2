#include "Utils.hpp"

void Utils::printColor(int color1, int color2, std::string texto) {
    std::cout << "\033["
              << color1 << ';'
              << color2 << 'm'
              << texto
              << "\033[0m"
              << std::endl;
}

void Utils::printColor(int color, std::string texto) {
    std::cout << "\033["
              << "1;"
              << color << 'm'
              << texto
              << "\033[0m"
              << std::endl;
}

void Utils::printColorNoLine(int color, std::string texto) {
    std::cout << "\033["
              << "1;"
              << color << 'm'
              << texto
              << "\033[0m";
}

void Utils::printColorNoLine(int color1, int color2, std::string texto) {
    std::cout << "\033["
              << color1 << ';'
              << color2 << 'm'
              << texto
              << "\033[0m";             
}


void Utils::limparConsole() {
    std::cout << u8"\033[2J\033[1;1H";
}
