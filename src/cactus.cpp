#include "cactus.hpp"
#include "bird.hpp"
#include "game.hpp"
#include <cstdint>
#include <ctime>
#include <random>
#include <ncurses.h>
#include <iostream>

using namespace std;

Cactus::Cactus() : m_rd(), m_gen(m_rd()) {}


void Cactus::setBounds(rect a) {
    m_field_bounds = a;
}

rect Cactus::getBounds() const {
    return m_field_bounds;
}

vector<Bird> Cactus::getObjects() const {
    return m_object_set;
}

bool Cactus::update(WINDOW* wnd, rect player_rect, int player_score) {
    // int dist_index = rand() % 2;
    uniform_int_distribution<int> dist01(0, 1);
    int dist_index = dist01(m_gen);

  /* Update existing objects */
  for (auto current_point{m_object_set.begin()};
       current_point != m_object_set.end(); ++current_point) {

    Bird &current_object = *current_point;

    if (current_object.getLastPos().x < m_field_bounds.left()) {
      m_object_set.erase(current_point);
    }

    if (current_object.getFielded() || current_point == m_object_set.begin()) {
      current_object.update(wnd);

      vector<vec2i> obj_pos = current_object.getPos();
      size_t length = current_object.getDispChar().size();
      rect object_rect = {{obj_pos[0].x, obj_pos[0].y},
                          {obj_pos[length - 1].x, obj_pos[length - 1].y}};

      if (isCollided(player_rect, object_rect)) {
        return true;
      }
    } else {
      auto previous_object = *(std::prev(current_point));

      int diff =
          abs(previous_object.getLastPos().x - current_object.getLastPos().x);
      if (dist_index == 0) {
        if (diff >= 60) {
          current_object.update(wnd);
        }
      }
    }
  }

  if (m_object_set.size() < 7) {
    int i = player_score > 500 ? 6 : 4;

    /* Spawn a new object */
    uniform_int_distribution<> distr(0, i);

    /* generate random number between 0 and 6 */
    auto object_type = distr(m_gen);
    rect fb = getBounds();

    string dc; /* Display characters */

    int y_start = 0;

    switch (object_type) {
    case 0: {
      y_start = 16;
      vector<vec2i> p{
          {fb.bounds.x - 6, y_start},     {fb.bounds.x - 5, y_start},
          {fb.bounds.x - 4, y_start},     {fb.bounds.x - 3, y_start},
          {fb.bounds.x - 2, y_start},     {fb.bounds.x - 1, y_start},
          {fb.bounds.x, y_start},         {fb.bounds.x - 6, y_start + 1},
          {fb.bounds.x - 5, y_start + 1}, {fb.bounds.x - 4, y_start + 1},
          {fb.bounds.x - 3, y_start + 1}, {fb.bounds.x - 2, y_start + 1},
          {fb.bounds.x - 1, y_start + 1}, {fb.bounds.x, y_start + 1},
          {fb.bounds.x - 6, y_start + 2}, {fb.bounds.x - 5, y_start + 2},
          {fb.bounds.x - 4, y_start + 2}, {fb.bounds.x - 3, y_start + 2},
          {fb.bounds.x - 2, y_start + 2}, {fb.bounds.x - 1, y_start + 2},
          {fb.bounds.x, y_start + 2},     {fb.bounds.x - 6, y_start + 3},
          {fb.bounds.x - 5, y_start + 3}, {fb.bounds.x - 4, y_start + 3},
          {fb.bounds.x - 3, y_start + 3}, {fb.bounds.x - 2, y_start + 3},
          {fb.bounds.x - 1, y_start + 3}, {fb.bounds.x, y_start + 3}};

      dc = "   _   "
           "  | |  "
           " _| |_ "
           "|_____|";

      Bird obj0{p, dc, 0};
      m_object_set.push_back(obj0);
      break;
    }

    case 1: {
      y_start = 15;
      vector<vec2i> p{
          {fb.bounds.x - 6, y_start},     {fb.bounds.x - 5, y_start},
          {fb.bounds.x - 4, y_start},     {fb.bounds.x - 3, y_start},
          {fb.bounds.x - 2, y_start},     {fb.bounds.x - 1, y_start},
          {fb.bounds.x, y_start},         {fb.bounds.x - 6, y_start + 1},
          {fb.bounds.x - 5, y_start + 1}, {fb.bounds.x - 4, y_start + 1},
          {fb.bounds.x - 3, y_start + 1}, {fb.bounds.x - 2, y_start + 1},
          {fb.bounds.x - 1, y_start + 1}, {fb.bounds.x, y_start + 1},
          {fb.bounds.x - 6, y_start + 2}, {fb.bounds.x - 5, y_start + 2},
          {fb.bounds.x - 4, y_start + 2}, {fb.bounds.x - 3, y_start + 2},
          {fb.bounds.x - 2, y_start + 2}, {fb.bounds.x - 1, y_start + 2},
          {fb.bounds.x, y_start + 2},     {fb.bounds.x - 6, y_start + 3},
          {fb.bounds.x - 5, y_start + 3}, {fb.bounds.x - 4, y_start + 3},
          {fb.bounds.x - 3, y_start + 3}, {fb.bounds.x - 2, y_start + 3},
          {fb.bounds.x - 1, y_start + 3}, {fb.bounds.x, y_start + 3},
          {fb.bounds.x - 6, y_start + 4}, {fb.bounds.x - 5, y_start + 4},
          {fb.bounds.x - 4, y_start + 4}, {fb.bounds.x - 3, y_start + 4},
          {fb.bounds.x - 2, y_start + 4}, {fb.bounds.x - 1, y_start + 4},
          {fb.bounds.x, y_start + 4}};

      dc = " _   _ "
           "| |_| |"
           "|_   _|"
           "  | |  "
           "__|_|__";

      Bird obj1{p, dc, 1};
      m_object_set.push_back(obj1);
      break;
    }

    case 2: {
      y_start = 13;
      vector<vec2i> p{
          {fb.bounds.x - 10, y_start},     {fb.bounds.x - 9, y_start},
          {fb.bounds.x - 8, y_start},      {fb.bounds.x - 7, y_start},
          {fb.bounds.x - 6, y_start},      {fb.bounds.x - 5, y_start},
          {fb.bounds.x - 4, y_start},      {fb.bounds.x - 3, y_start},
          {fb.bounds.x - 2, y_start},      {fb.bounds.x - 1, y_start},
          {fb.bounds.x, y_start},          {fb.bounds.x - 10, y_start + 1},
          {fb.bounds.x - 9, y_start + 1},  {fb.bounds.x - 8, y_start + 1},
          {fb.bounds.x - 7, y_start + 1},  {fb.bounds.x - 6, y_start + 1},
          {fb.bounds.x - 5, y_start + 1},  {fb.bounds.x - 4, y_start + 1},
          {fb.bounds.x - 3, y_start + 1},  {fb.bounds.x - 2, y_start + 1},
          {fb.bounds.x - 1, y_start + 1},  {fb.bounds.x, y_start + 1},
          {fb.bounds.x - 10, y_start + 2}, {fb.bounds.x - 9, y_start + 2},
          {fb.bounds.x - 8, y_start + 2},  {fb.bounds.x - 7, y_start + 2},
          {fb.bounds.x - 6, y_start + 2},  {fb.bounds.x - 5, y_start + 2},
          {fb.bounds.x - 4, y_start + 2},  {fb.bounds.x - 3, y_start + 2},
          {fb.bounds.x - 2, y_start + 2},  {fb.bounds.x - 1, y_start + 2},
          {fb.bounds.x, y_start + 2},      {fb.bounds.x - 10, y_start + 3},
          {fb.bounds.x - 9, y_start + 3},  {fb.bounds.x - 8, y_start + 3},
          {fb.bounds.x - 7, y_start + 3},  {fb.bounds.x - 6, y_start + 3},
          {fb.bounds.x - 5, y_start + 3},  {fb.bounds.x - 4, y_start + 3},
          {fb.bounds.x - 3, y_start + 3},  {fb.bounds.x - 2, y_start + 3},
          {fb.bounds.x - 1, y_start + 3},  {fb.bounds.x, y_start + 3},
          {fb.bounds.x - 10, y_start + 4}, {fb.bounds.x - 9, y_start + 4},
          {fb.bounds.x - 8, y_start + 4},  {fb.bounds.x - 7, y_start + 4},
          {fb.bounds.x - 6, y_start + 4},  {fb.bounds.x - 5, y_start + 4},
          {fb.bounds.x - 4, y_start + 4},  {fb.bounds.x - 3, y_start + 4},
          {fb.bounds.x - 2, y_start + 4},  {fb.bounds.x - 1, y_start + 4},
          {fb.bounds.x, y_start + 4},      {fb.bounds.x - 10, y_start + 5},
          {fb.bounds.x - 9, y_start + 5},  {fb.bounds.x - 8, y_start + 5},
          {fb.bounds.x - 7, y_start + 5},  {fb.bounds.x - 6, y_start + 5},
          {fb.bounds.x - 5, y_start + 5},  {fb.bounds.x - 4, y_start + 5},
          {fb.bounds.x - 3, y_start + 5},  {fb.bounds.x - 2, y_start + 5},
          {fb.bounds.x - 1, y_start + 5},  {fb.bounds.x, y_start + 5},
          {fb.bounds.x - 10, y_start + 6}, {fb.bounds.x - 9, y_start + 6},
          {fb.bounds.x - 8, y_start + 6},  {fb.bounds.x - 7, y_start + 6},
          {fb.bounds.x - 6, y_start + 6},  {fb.bounds.x - 5, y_start + 6},
          {fb.bounds.x - 4, y_start + 6},  {fb.bounds.x - 3, y_start + 6},
          {fb.bounds.x - 2, y_start + 6},  {fb.bounds.x - 1, y_start + 6},
          {fb.bounds.x, y_start + 6}};

      dc = "     _     "
           "    | |    "
           " _  | |  _ "
           "| |_| |_| |"
           "|___   ___|"
           "    | |    "
           "____|_|____";

      Bird obj2{p, dc, 2};
      m_object_set.push_back(obj2);
      break;
    }

    case 3: {
      y_start = 16;
      vector<vec2i> p{
          {fb.bounds.x - 10, y_start},     {fb.bounds.x - 9, y_start},
          {fb.bounds.x - 8, y_start},      {fb.bounds.x - 7, y_start},
          {fb.bounds.x - 6, y_start},      {fb.bounds.x - 5, y_start},
          {fb.bounds.x - 4, y_start},      {fb.bounds.x - 3, y_start},
          {fb.bounds.x - 2, y_start},      {fb.bounds.x - 1, y_start},
          {fb.bounds.x, y_start},          {fb.bounds.x - 10, y_start + 1},
          {fb.bounds.x - 9, y_start + 1},  {fb.bounds.x - 8, y_start + 1},
          {fb.bounds.x - 7, y_start + 1},  {fb.bounds.x - 6, y_start + 1},
          {fb.bounds.x - 5, y_start + 1},  {fb.bounds.x - 4, y_start + 1},
          {fb.bounds.x - 3, y_start + 1},  {fb.bounds.x - 2, y_start + 1},
          {fb.bounds.x - 1, y_start + 1},  {fb.bounds.x, y_start + 1},
          {fb.bounds.x - 10, y_start + 2}, {fb.bounds.x - 9, y_start + 2},
          {fb.bounds.x - 8, y_start + 2},  {fb.bounds.x - 7, y_start + 2},
          {fb.bounds.x - 6, y_start + 2},  {fb.bounds.x - 5, y_start + 2},
          {fb.bounds.x - 4, y_start + 2},  {fb.bounds.x - 3, y_start + 2},
          {fb.bounds.x - 2, y_start + 2},  {fb.bounds.x - 1, y_start + 2},
          {fb.bounds.x, y_start + 2},      {fb.bounds.x - 10, y_start + 3},
          {fb.bounds.x - 9, y_start + 3},  {fb.bounds.x - 8, y_start + 3},
          {fb.bounds.x - 7, y_start + 3},  {fb.bounds.x - 6, y_start + 3},
          {fb.bounds.x - 5, y_start + 3},  {fb.bounds.x - 4, y_start + 3},
          {fb.bounds.x - 3, y_start + 3},  {fb.bounds.x - 2, y_start + 3},
          {fb.bounds.x - 1, y_start + 3},  {fb.bounds.x, y_start + 3}};

      dc = "     _     "
           " _  | |  _ "
           "| |_| |_| |"
           "|_________|";

      Bird obj3{p, dc, 3};
      m_object_set.push_back(obj3);
      break;
    }

    case 4: {
      y_start = 14;
      vector<vec2i> p{
          {fb.bounds.x - 6, y_start},     {fb.bounds.x - 5, y_start},
          {fb.bounds.x - 4, y_start},     {fb.bounds.x - 3, y_start},
          {fb.bounds.x - 2, y_start},     {fb.bounds.x - 1, y_start},
          {fb.bounds.x, y_start},         {fb.bounds.x - 6, y_start + 1},
          {fb.bounds.x - 5, y_start + 1}, {fb.bounds.x - 4, y_start + 1},
          {fb.bounds.x - 3, y_start + 1}, {fb.bounds.x - 2, y_start + 1},
          {fb.bounds.x - 1, y_start + 1}, {fb.bounds.x, y_start + 1},
          {fb.bounds.x - 6, y_start + 2}, {fb.bounds.x - 5, y_start + 2},
          {fb.bounds.x - 4, y_start + 2}, {fb.bounds.x - 3, y_start + 2},
          {fb.bounds.x - 2, y_start + 2}, {fb.bounds.x - 1, y_start + 2},
          {fb.bounds.x, y_start + 2},     {fb.bounds.x - 6, y_start + 3},
          {fb.bounds.x - 5, y_start + 3}, {fb.bounds.x - 4, y_start + 3},
          {fb.bounds.x - 3, y_start + 3}, {fb.bounds.x - 2, y_start + 3},
          {fb.bounds.x - 1, y_start + 3}, {fb.bounds.x, y_start + 3},
          {fb.bounds.x - 6, y_start + 4}, {fb.bounds.x - 5, y_start + 4},
          {fb.bounds.x - 4, y_start + 4}, {fb.bounds.x - 3, y_start + 4},
          {fb.bounds.x - 2, y_start + 4}, {fb.bounds.x - 1, y_start + 4},
          {fb.bounds.x, y_start + 4},     {fb.bounds.x - 6, y_start + 5},
          {fb.bounds.x - 5, y_start + 5}, {fb.bounds.x - 4, y_start + 5},
          {fb.bounds.x - 3, y_start + 5}, {fb.bounds.x - 2, y_start + 5},
          {fb.bounds.x - 1, y_start + 5}, {fb.bounds.x, y_start + 5}};

      dc = " _   _ "
           "| | | |"
           "| |_| |"
           "|_   _|"
           "  | |  "
           "__|_|__";

      Bird obj4{p, dc, 4};
      m_object_set.push_back(obj4);
      break;
    }

    case 5: {
      y_start = 7;
      vector<vec2i> p{
          {fb.bounds.x - 8, y_start},     {fb.bounds.x - 7, y_start},
          {fb.bounds.x - 6, y_start},     {fb.bounds.x - 5, y_start},
          {fb.bounds.x - 4, y_start},     {fb.bounds.x - 3, y_start},
          {fb.bounds.x - 2, y_start},     {fb.bounds.x - 1, y_start},
          {fb.bounds.x, y_start},         {fb.bounds.x - 8, y_start + 1},
          {fb.bounds.x - 7, y_start + 1}, {fb.bounds.x - 6, y_start + 1},
          {fb.bounds.x - 5, y_start + 1}, {fb.bounds.x - 4, y_start + 1},
          {fb.bounds.x - 3, y_start + 1}, {fb.bounds.x - 2, y_start + 1},
          {fb.bounds.x - 1, y_start + 1}, {fb.bounds.x, y_start + 1},
          {fb.bounds.x - 8, y_start + 2}, {fb.bounds.x - 7, y_start + 2},
          {fb.bounds.x - 6, y_start + 2}, {fb.bounds.x - 5, y_start + 2},
          {fb.bounds.x - 4, y_start + 2}, {fb.bounds.x - 3, y_start + 2},
          {fb.bounds.x - 2, y_start + 2}, {fb.bounds.x - 1, y_start + 2},
          {fb.bounds.x, y_start + 2},     {fb.bounds.x - 8, y_start + 3},
          {fb.bounds.x - 7, y_start + 3}, {fb.bounds.x - 6, y_start + 3},
          {fb.bounds.x - 5, y_start + 3}, {fb.bounds.x - 4, y_start + 3},
          {fb.bounds.x - 3, y_start + 3}, {fb.bounds.x - 2, y_start + 3},
          {fb.bounds.x - 1, y_start + 3}, {fb.bounds.x, y_start + 3},
          {fb.bounds.x - 8, y_start + 4}, {fb.bounds.x - 7, y_start + 4},
          {fb.bounds.x - 6, y_start + 4}, {fb.bounds.x - 5, y_start + 4},
          {fb.bounds.x - 4, y_start + 4}, {fb.bounds.x - 3, y_start + 4},
          {fb.bounds.x - 2, y_start + 4}, {fb.bounds.x - 1, y_start + 4},
          {fb.bounds.x, y_start + 4},     {fb.bounds.x - 8, y_start + 5},
          {fb.bounds.x - 7, y_start + 5}, {fb.bounds.x - 6, y_start + 5},
          {fb.bounds.x - 5, y_start + 5}, {fb.bounds.x - 4, y_start + 5},
          {fb.bounds.x - 3, y_start + 5}, {fb.bounds.x - 2, y_start + 5},
          {fb.bounds.x - 1, y_start + 5}, {fb.bounds.x, y_start + 5},
          {fb.bounds.x - 8, y_start + 6}, {fb.bounds.x - 7, y_start + 6},
          {fb.bounds.x - 6, y_start + 6}, {fb.bounds.x - 5, y_start + 6},
          {fb.bounds.x - 4, y_start + 6}, {fb.bounds.x - 3, y_start + 6},
          {fb.bounds.x - 2, y_start + 6}, {fb.bounds.x - 1, y_start + 6},
          {fb.bounds.x, y_start + 6},
      };

      dc = "         "
           "         "
           "  _____  "
           ">|_   _\\="
           "   | /   "
           "   |/    "
           "   '     ";

      Bird obj5{p, dc, 5};
      m_object_set.push_back(obj5);
      break;
    }

    case 6: {
      y_start = 13;
      vector<vec2i> p{
          {fb.bounds.x - 8, y_start},     {fb.bounds.x - 7, y_start},
          {fb.bounds.x - 6, y_start},     {fb.bounds.x - 5, y_start},
          {fb.bounds.x - 4, y_start},     {fb.bounds.x - 3, y_start},
          {fb.bounds.x - 2, y_start},     {fb.bounds.x - 1, y_start},
          {fb.bounds.x, y_start},         {fb.bounds.x - 8, y_start + 1},
          {fb.bounds.x - 7, y_start + 1}, {fb.bounds.x - 6, y_start + 1},
          {fb.bounds.x - 5, y_start + 1}, {fb.bounds.x - 4, y_start + 1},
          {fb.bounds.x - 3, y_start + 1}, {fb.bounds.x - 2, y_start + 1},
          {fb.bounds.x - 1, y_start + 1}, {fb.bounds.x, y_start + 1},
          {fb.bounds.x - 8, y_start + 2}, {fb.bounds.x - 7, y_start + 2},
          {fb.bounds.x - 6, y_start + 2}, {fb.bounds.x - 5, y_start + 2},
          {fb.bounds.x - 4, y_start + 2}, {fb.bounds.x - 3, y_start + 2},
          {fb.bounds.x - 2, y_start + 2}, {fb.bounds.x - 1, y_start + 2},
          {fb.bounds.x, y_start + 2},     {fb.bounds.x - 8, y_start + 3},
          {fb.bounds.x - 7, y_start + 3}, {fb.bounds.x - 6, y_start + 3},
          {fb.bounds.x - 5, y_start + 3}, {fb.bounds.x - 4, y_start + 3},
          {fb.bounds.x - 3, y_start + 3}, {fb.bounds.x - 2, y_start + 3},
          {fb.bounds.x - 1, y_start + 3}, {fb.bounds.x, y_start + 3},
          {fb.bounds.x - 8, y_start + 4}, {fb.bounds.x - 7, y_start + 4},
          {fb.bounds.x - 6, y_start + 4}, {fb.bounds.x - 5, y_start + 4},
          {fb.bounds.x - 4, y_start + 4}, {fb.bounds.x - 3, y_start + 4},
          {fb.bounds.x - 2, y_start + 4}, {fb.bounds.x - 1, y_start + 4},
          {fb.bounds.x, y_start + 4},     {fb.bounds.x - 8, y_start + 5},
          {fb.bounds.x - 7, y_start + 5}, {fb.bounds.x - 6, y_start + 5},
          {fb.bounds.x - 5, y_start + 5}, {fb.bounds.x - 4, y_start + 5},
          {fb.bounds.x - 3, y_start + 5}, {fb.bounds.x - 2, y_start + 5},
          {fb.bounds.x - 1, y_start + 5}, {fb.bounds.x, y_start + 5},
          {fb.bounds.x - 8, y_start + 6}, {fb.bounds.x - 7, y_start + 6},
          {fb.bounds.x - 6, y_start + 6}, {fb.bounds.x - 5, y_start + 6},
          {fb.bounds.x - 4, y_start + 6}, {fb.bounds.x - 3, y_start + 6},
          {fb.bounds.x - 2, y_start + 6}, {fb.bounds.x - 1, y_start + 6},
          {fb.bounds.x, y_start + 6},
      };

      dc = "         "
           "         "
           "  _____  "
           ">|_   _\\="
           "   | /   "
           "   |/    "
           "___'_____";

      Bird obj6{p, dc, 6};
      m_object_set.push_back(obj6);
      break;
    }
    }
  }

  return false;
}
