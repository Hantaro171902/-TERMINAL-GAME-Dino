#pragma once 

#include <string>
#include <vector>
#include "color.hpp"

class Dinosaur {
private:
    int h0; // Initial height
    int t;  // Time since last jump

public:
    Dinosaur();
    void update(bool jump);
    int get_position() const;
    void draw(std::vector<std::vector<Pixel>>& screen, int frame) const;
    bool crashed(int ceiling, int floor) const;
    bool crashed_into(int obs_col, int obs_height) const;
}