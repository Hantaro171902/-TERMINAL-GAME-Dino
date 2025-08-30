#pragma once

#include <string>
#include <vector>
#include <ncurses.h>
#include <random>
#include "utils.hpp"
#include "game.hpp"


class Bird {
public:
    Bird(std::vector<vec2i>, std::string, int);
    void render(WINDOW*);
    void update(WINDOW*);
    vec2i getLastPos() const;
    std::vector<vec2i> getPos() const;
    std::string getDispChar() const;
    bool getFielded();
    void feildedToTrue();

private:
    std::vector<vec2i> m_positions;
    std::string m_disp_char;
    int m_type;
    bool m_fielded;
};


