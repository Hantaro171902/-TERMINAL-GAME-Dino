#pragma once 

#include <iostream>
#include <string>
#include <vector>

struct vec2i {
    int x;
    int y;
};

struct rect {
    vec2i top_left;
    vec2i bottom_right;

    int top() const { return top_left.y; };
    int bot() const { return bottom_right.y; }
    int left() const { return top_left.x; }
    int right() const { return bottom_right.x; }
    int width() const { return right() - left(); }
    int height() const { return bot() - top(); }
};

bool isCollided(const rect& a, const rect& b);
