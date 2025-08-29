#include "bird.hpp"
#include <ncurses.h>

void Bird::draw(WINDOW* wnd) {
    // Draw the bird on the window
    for (size_t i = 0; i < disp.size(); i++) {
        mvaddch(wnd, pos[i].y, pos[i].x, disp[i]);
    }
}

void Bird::update(WINDOW* wnd) {
    for (auto& p : pos) {
        p.x--;
    }
    update(wnd);
}
