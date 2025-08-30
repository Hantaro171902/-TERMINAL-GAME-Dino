#pragma once

#include <string>
#include <vector>
#include <string>
#include <ncurses.h>
#include <iostream>
#include <random>
#include "game.hpp"

class Cactus {
public:
    Cactus();
	bool update(WINDOW*, rect, int);
	std::vector<Cactus> getObjects() const;
	void setBounds(rect);
	rect getBounds();
private:
    std::random_device m_rd;
    std::mt19937 m_gen;
	rect m_field_bounds;
	std::vector<Cactus> m_object_set;
};