#pragma once

#include <string>
#include <vector>
#include <ncurses.h>
#include <random>

#include "game.hpp"
#include "bird.hpp"   // Bird is the individual obstacle class

class Cactus {
public:
    Cactus();

    // update returns true when collision happened
    bool update(WINDOW* wnd, rect player_rect, int player_score);

    // return the objects currently in the field
    std::vector<Bird> getObjects() const;

    void setBounds(rect a);
    rect getBounds() const;

private:
    std::random_device m_rd;
    std::mt19937 m_gen;

    rect m_field_bounds;

    // store Birds (individual obstacles). Bird is copyable/movable.
    std::vector<Bird> m_object_set;
};