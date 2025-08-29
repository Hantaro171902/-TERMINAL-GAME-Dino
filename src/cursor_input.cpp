#include <ncurses.h>
#include <iostream>

using namespace std;

void initInput(WINDOW* main, WINDOW* game) {
    cbreak();
    noecho();
    curs_set(0);
    keypad(main, TRUE);
    keypad(game, TRUE);
    nodelay(main, TRUE);
    nodelay(game, TRUE);
}

int getInput(WINDOW* wnd) {
    int ch = wgetch(wnd);
    return tolower(ch);
}