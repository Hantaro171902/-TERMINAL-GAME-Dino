#include "color.hpp"
#include <iostream>

using namespace std;

void setTextColor(TextColor color) {
    cout << "\033[" << color << "m";
}

void setBackgroundColor(TextColor bg_color) {
    cout << "\033[" << bg_color << "m";
}

void setTextAndBackground(TextColor text_color, TextColor bg_color) {
    cout << "\033[" << text_color << ";" << bg_color << "m";
}

void resetTextColor() {
    cout << "\033[0m";
}

void clearScreen() {
    cout << "\033[2J";
}

void moveCursor(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}

void hideCursor() {
    cout << "\033[?25l";
}

void showCursor() {
    cout << "\033[?25h";
}
