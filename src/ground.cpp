#include "ground.hpp"
#include "game.hpp"
#include "ansi_renderer.hpp"
#include <cstdint>
#include <ctime>
#include <random>
#include <iostream>

using namespace std;

Ground::Ground(int x, int y, char disp_char) {
  m_position.x = x;
  m_position.y = y;
  m_disp_char = disp_char;
}

void Ground::update(ANSIRenderer *game_renderer) {
  game_renderer->drawChar(m_position.x, m_position.y, ' ', DEFAULT, DEFAULT);
  m_position.x -= 1;
  game_renderer->drawChar(m_position.x, m_position.y, m_disp_char, GROUND_TEXT, GROUND_BG);
}

vec2i Ground::getPos() const { return m_position; }

// --- GROUND FIELD --- 

void GroundField::update(ANSIRenderer *game_renderer) {
  for (auto dirt_index{m_dirt_field.begin()}; dirt_index != m_dirt_field.end();
       ++dirt_index) {
    auto &dirt = *dirt_index;
    if (dirt.getPos().x < m_dirt_bounds.left()) {
      m_dirt_field.erase(dirt_index);
    }

    dirt.update(game_renderer);
  }

  random_device rd;  /* Obtain random number from hardware */
  mt19937 gen(rd()); /* Seed the generator */
  uniform_int_distribution<> distr(20, 22);
  uniform_int_distribution<> dirt_distribution(0, 4);

  auto y_cord = distr(gen);

  auto dirt_type = dirt_distribution(gen);

  if (dirt_type == 0) {
    Ground dirt(m_dirt_bounds.width(), y_cord, '.');
    m_dirt_field.push_back(dirt);
  } else if (dirt_type == 1) {
    Ground dirt(m_dirt_bounds.width(), y_cord, '-');
    m_dirt_field.push_back(dirt);
  } else if (dirt_type == 2) {
    Ground dirt(m_dirt_bounds.width(), y_cord, '_');
    m_dirt_field.push_back(dirt);
  } else if (dirt_type == 3) {
    Ground dirt(m_dirt_bounds.width(), y_cord, '\'');
    m_dirt_field.push_back(dirt);
  } else {
    Ground dirt(m_dirt_bounds.width(), y_cord, '`');
    m_dirt_field.push_back(dirt);
  }
}

void GroundField::setBounds(rect a) { m_dirt_bounds = a; }

void GroundField::seed() {
  random_device rd; /* Obtain random number from hardware */
  mt19937 gen(rd());
  uniform_int_distribution<> distr(20, 22);
  uniform_int_distribution<> distr2(0, 78);
  uniform_int_distribution<> dirt_distribution(0, 4);

  for (size_t i = 0; i < 100; i++) {

    auto dirt_type = dirt_distribution(gen);
    auto y_cord = distr(gen);
    auto x_cord = distr2(gen);

    if (dirt_type == 0) {
      Ground dirt(x_cord, y_cord, '.');
      m_dirt_field.push_back(dirt);
    } else if (dirt_type == 1) {
      Ground dirt(x_cord, y_cord, '-');
      m_dirt_field.push_back(dirt);
    } else if (dirt_type == 2) {
      Ground dirt(x_cord, y_cord, '_');
      m_dirt_field.push_back(dirt);
    } else if (dirt_type == 3) {
      Ground dirt(x_cord, y_cord, '\'');
      m_dirt_field.push_back(dirt);
    } else {
      Ground dirt(x_cord, y_cord, '`');
      m_dirt_field.push_back(dirt);
    }
  }
}

rect GroundField::getBounds() { return m_dirt_bounds; }
