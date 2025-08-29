#pragma once 

#include <string>
#include <ncurses.h>
#include <string>
#include <vector>
#include "utils.hpp"

struct Dinosaur {
    std::vector<vec2i> pos;
    std::string disp;
    rect bounds;
    bool jumping = false;
    bool crouching = false;
    int air_time = 0;
    int max_air_time = 40;
    int score = 0;

    void draw(WINDOW* wnd);
    void jump(WINDOW* wnd);
    void crouch(WINDOW* wnd);
    void updateBounds();
}