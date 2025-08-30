#pragma once

#include <string>
#include <vector>
#include <ncurses.h>
#include <random>
#include "game.hpp"


class Ground;
class Cactus;

class Bird {
public:
    Bird(std::vector<vec2i>, std::string, int);
    void render(WINDOW*);
    void update(WINDOW*);
    vec2i getLastPos() const;
    std::vector<vec2i> getPos() const;
    std::string getDispChar() const;
    bool getFielded();
    void fieldedToTrue();

private:
    std::vector<vec2i> m_positions;
    std::string m_disp_char;
    int m_type;
    bool m_fielded;
};


