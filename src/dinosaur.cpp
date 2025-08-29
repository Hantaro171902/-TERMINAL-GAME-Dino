#include "dinosaur.hpp"
#include <ncurses.h>

void Dinosaur::draw(WINDOW* wnd) {
    // Draw the dinosaur on the window
    for (size_t i = 0; i < disp.size(); i++) {
        mvwprintw(wnd, pos[i].y, pos[i].x, disp[i]);
    }
}

void Dinosaur::jump(WINDOW* wnd) {
    if (!jumping) {
        jumping = true;
        air_time = 0;
    }
}

void Dinosaur::crouch(WINDOW* wnd) {
    crouching = true;
}

void Dinosaur::updateBounds() {
    // Update the bounding box of the dinosaur
    bounds = { pos.front(), pos.back() };   
}