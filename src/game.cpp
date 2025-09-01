#include "game.hpp"
#include "dinosaur.hpp"
#include "ground.hpp"
#include "cactus.hpp"
#include "bird.hpp"
#include "ansi_renderer.hpp"

#include <unistd.h>
#include <vector>
#include <chrono>
#include <random>
#include <iostream>
#include <sys/select.h>
#include <cstdlib>
#include <cstdio>

using namespace std;

ANSIRenderer *main_renderer;
ANSIRenderer *game_renderer;

rect game_area;
rect screen_area;
rect dirt_area;

bool isCollided(rect a, rect b) {
    bool a1 = (a.top() < b.bot() - b.top());
    bool b1 = (a.bot() - a.top() > b.top());
    bool c1 = (a.right() - a.left() > b.left());
    bool d1 = (a.left() < b.right() - b.left());

    return (a1 && b1 && c1 && d1);
}

int init() {
    srand(static_cast<unsigned>(time(nullptr)));

    screen_area = {{0, 0}, {80, 24}};
    game_area = {{0, 0}, {screen_area.width() - 2, screen_area.height() - 2}};
    dirt_area = {{0, 19}, {screen_area.width() - 2, screen_area.height() - 2}};

    // Create renderers
    main_renderer = new ANSIRenderer(screen_area.width(), screen_area.height());
    game_renderer = new ANSIRenderer(game_area.width(), game_area.height());

    return 0;
}


bool run(int &max_score) {
  Cactus field;
  GroundField df;

  Player player;
  player.up = false;
  player.score = 0;

  int tick = 0;

  int speed_tick = 0;
  int speed_tick_cap = 2; /* Increment or decrement to control obstacl speed */

  int dirt_tick = 0;
  const int dirt_tick_cap = 2;

  player.air_time = 0;
  player.max_air_time =
      58; /* Increment or decrement to control player air time */

  int feet_tick = 0;

  int in_char = 0;

  bool game_over = false;

  field.setBounds(game_area);
  df.setBounds(dirt_area);

  // frame around screen
  main_renderer->drawBox(0, 0, screen_area.width(), screen_area.height(), WHITE, DEFAULT);

  // initial draw
  main_renderer->refresh();
  game_renderer->refresh();

  // mvwprintw(main_wnd, 0, 0, "press SPACE to start...");

  // Seed dirt field
  df.seed();
  df.update(game_renderer);

  // Draw dino to terminal
  initPlayerPosition(game_renderer, &player);
  game_renderer->drawLine(0, screen_area.bot() - 5, screen_area.width() - 2, '_', WHITE, DEFAULT);
  game_renderer->refresh();

  while (1) {
    // Simple input handling without ncurses
    if (system("stty -icanon -echo") == 0) {
        system("stty -icanon -echo");
    }
    
    // Check for input (non-blocking)
    fd_set readfds;
    struct timeval tv;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    tv.tv_sec = 0;
    tv.tv_usec = 10000; // 10ms timeout
    
    if (select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv) > 0) {
        in_char = getchar();
        in_char = tolower(in_char);
    } else {
        in_char = 0; // No input
    }

    if (player.air_time == player.max_air_time && player.up) {
      player.air_time = 0;
      player.up = false;

      movePlayerDown(game_wnd, &player);
    }

    switch (in_char) {
    case KEY_UP:
    case ' ':
    case 'w':
      if (!player.up) {
        movePlayerUp(game_wnd, &player);
        player.up = true;
      }
      break;
    case KEY_DOWN:
    case 's':
      if (player.up) { /* Cancel jump */
        player.air_time = 0;
        player.up = false;

        movePlayerDown(game_wnd, &player);
        break;
      }

      crouchPlayer(game_wnd, &player);
      break;
    default:
      break;
    }

    size_t p_length = player.disp_char.size();
    size_t c_length = player.crouch_disp_char.size();
    if (player.crouched) {
      player.bounds = {{player.crouch_pos[0].x, player.crouch_pos[0].y},
                       {player.crouch_pos[c_length - 1].x,
                        player.crouch_pos[c_length - 1].y}};
    } else {
      player.bounds = {
          {player.pos[0].x, player.pos[0].y},
          {player.pos[p_length - 1].x, player.pos[p_length - 1].y}};
    }

    if (tick >= 200) {
      speed_tick++;
      if (speed_tick == speed_tick_cap) {
        speed_tick = 0;
        if (field.update(game_renderer, player.bounds, player.score)) {
          /* Collision occured; game over*/
          game_over = true;
        };
      }
    }

    if (dirt_tick == dirt_tick_cap) {
      dirt_tick = 0;
      df.update(game_renderer);
    }

    if (feet_tick == 17) {
      feet_tick = 0;
      if (!player.up)
        playerFeetAnimation(game_renderer, &player);
    }

    main_renderer->refresh();
    game_renderer->refresh();

    if (game_over) {
      max_score = player.score > max_score ? player.score : max_score;
      // Print game over message and prompt user for input
      int input;
      game_renderer->drawString(35, 9, "GAME OVER", WHITE, DEFAULT);
      game_renderer->drawString(29, 11, "press 'q' to exit", WHITE, DEFAULT);
      game_renderer->drawString(29, 12, "press 'r' to retry", WHITE, DEFAULT);
      game_renderer->refresh();
      usleep(50000); /* Gotta let the gamer read the info */

      while (1) {
        input = getchar();
        input = tolower(input);

        switch (input) {
        case 'r':
          return false; // quit game
        case 'q':
          return true;
        }
      }
    }

    if (player.up)
      player.air_time++;

    if (tick % 5 == 0) {
      // increase player score
      player.score += 1;
    }

    char score_str[100];
    sprintf(score_str, "HIGH SCORE: %8d", max_score);
    game_renderer->drawString(58, 0, score_str, SCORE_COLOR, DEFAULT);
    sprintf(score_str, "CURRENT SCORE: %8d", player.score);
    game_renderer->drawString(55, 1, score_str, SCORE_COLOR, DEFAULT);
    game_renderer->refresh();

    feet_tick++;
    dirt_tick++;
    tick++;

    if (player.score > 1500) {
      speed_tick_cap = 1;
      player.max_air_time = 43;
    }

    usleep(10000);
  }
}

void close() { 
    delete main_renderer;
    delete game_renderer;
}
