#pragma once

#include <random>
#include <vector>
#include <string>
#include "ansi_renderer.hpp"
#include "game.hpp"


class Ground {
public:
	Ground(int, int, char);
	void update(class ANSIRenderer*);
	vec2i getPos() const;
private:
	char m_disp_char;
	vec2i m_position;
};

class GroundField {
public:
	void update(class ANSIRenderer*);
	void setBounds(rect);
	void seed();
	rect getBounds();
private:
	rect m_dirt_bounds;
	std::vector<Ground> m_dirt_field;	
};
