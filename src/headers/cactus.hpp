#pragma once

#include <string>
#include <vector>
#include "utils.hpp"

struct Cactus {
    std::vector<vec2i> pos;
    std::string disp;
    rect bounds;
    bool active = true;

    void draw(WINDOW* wnd);
    void updateBounds();
}