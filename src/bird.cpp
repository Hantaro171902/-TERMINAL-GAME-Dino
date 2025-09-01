#include "bird.hpp"
#include "game.hpp"
#include "ansi_renderer.hpp"
#include <cstdint>
#include <ctime>
#include <random>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int tick = 0;

Bird::Bird(std::vector<vec2i> pos, std::string disp_char, int type)
    : m_positions(pos), m_disp_char(disp_char), m_type(type), m_fielded(false) {
}


vec2i Bird::getLastPos() const {
  return m_positions[m_disp_char.size() - 1];
}

vector<vec2i> Bird::getPos() const { return m_positions; }

string Bird::getDispChar() const { return m_disp_char; }

void Bird::fieldedToTrue() { m_fielded = true; }

void Bird::update(ANSIRenderer *game_renderer) {
  for (size_t i = 0; i < m_disp_char.size(); i++) {
    if (m_positions[i].y == 19) {
      game_renderer->drawChar(m_positions[i].x, m_positions[i].y, '_', WHITE, DEFAULT);
    } else {
      game_renderer->drawChar(m_positions[i].x, m_positions[i].y, ' ', DEFAULT, DEFAULT);
    }
  }

  render(game_renderer);
  fieldedToTrue(); /* Object is now in the object field/game window */
}

void Bird::render(ANSIRenderer *game_renderer) {
  if (m_type == 6 && tick >= 20) {
    tick = 0;
    if (m_disp_char[5] == ',') {
      m_disp_char = "         "
                    "         "
                    "  _____  "
                    ">|_   _\\="
                    "   | /   "
                    "   |/    "
                    "___'_____";

    } else if (m_disp_char[5] == ' ') {

      m_disp_char = "     ,   "
                    "    /|   "
                    "  _/ |_  "
                    ">|_____\\="
                    "         "
                    "         "
                    "_________";
    }
  } else if (m_type == 5 && tick >= 20) {
    tick = 0;
    if (m_disp_char[5] == ',') {
      m_disp_char = "         "
                    "         "
                    "  _____  "
                    ">|_   _\\="
                    "   | /   "
                    "   |/    "
                    "   '     ";

    } else if (m_disp_char[5] == ' ') {

      m_disp_char = "     ,   "
                    "    /|   "
                    "  _/ |_  "
                    ">|_____\\="
                    "         "
                    "         "
                    "         ";
    }
  }

  for (size_t i = 0; i < m_disp_char.size(); i++) {
    m_positions[i].x -= 1;
    game_renderer->drawChar(m_positions[i].x, m_positions[i].y, m_disp_char[i], OBSTACLE_COLOR, DEFAULT);
  }
  tick++;
}

bool Bird::getFielded() { return m_fielded; }