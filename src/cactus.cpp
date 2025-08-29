#include "cactus.hpp"
#include <ncurses.h>

void Cactus::draw(WINDOW* wnd) {
    // Draw the cactus on the window
    for (size_t i = 0; i < disp.size(); i++) {
        mvaddch(wnd, pos[i].y, pos[i].x, disp[i]);
    }
}

void Cactus::update(WINDOW* wnd) {
    for (auto& p : pos) {
        p.x--;
    }
    update(wnd);
}
