#include "game.hpp"
#include "cursor_input.hpp"
#include "color.hpp"
#include "dinosaur.hpp"
#include "cactus.hpp"
#include "bird.hpp"

#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <chrono>
#include <random>
#include <iostream>

using namespace std;

WINDOW *main_wnd;
WINDOW *game_wnd;

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

    main_wnd - initscr();

    cbreak();
    noecho();
    clear();
    refresh();

    curs_set(0);

    start_color()

    screen_area = {{0, 0}, {80, 24}};

    game_wnd = newwin(screen_area.height() - 2, screen_area.width() - 2,
                    screen_area.top() + 1, screen_area.left() + 1);

    main_wnd = newwin(screen_area.height(), screen_area.width(), 0, 0);

    game_area = {{0, 0}, {screen_area.width() - 2, screen_area.height() - 2}};

    dirt_area = {{0, 19}, {screen_area.width() - 2, screen_area.height() - 2}};

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    /* Enable function keys */
    keypad(main_wnd, true);
    keypad(game_wnd, true);

    nodelay(main_wnd, true);
    nodelay(game_wnd, true);

    if (!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n");
        exit(1);
    }

    return 0;
}


bool run(int &max_score) {
    Player player;
    int start_x = 5;
    player.initDefault(start_x, ground_y);
    player.max_air_time = 20;

    std::vector<Cactus> cactuses;
    std::vector<Bird> birds;

    bool game_over = false;
    int tick = 0;
    int spawn_ticks = 0;
    int spawn_interval = 40; // frames between obstacle attempts
    int score = 0;

    std::mt19937 rng((unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> birdchance(0, 4);
    std::uniform_int_distribution<int> birdheight(ground_y - 6, ground_y - 10);

    // initial ground draw
    werase(game_wnd);
    mvwhline(game_wnd, ground_y, 0, '_', screen_w-2);
    wrefresh(game_wnd);

    // game loop
    while (true) {
        int ch = getInputNonBlocking();
        if (ch != ERR) {
            if (ch == 'q') {
                return true; // quit whole program
            } else if (ch == 'r' && game_over) {
                return false; // retry the game
            } else if ((ch == ' ' || ch == 'w' || ch == KEY_UP) && !game_over) {
                if (!player.up) {
                    player.moveUp();
                }
            } else if ((ch == 's' || ch == KEY_DOWN) && !game_over) {
                player.crouch();
            } else if (ch == ERR) {
                // nothing
            }
        }

        // Clear window and redraw
        werase(game_wnd);
        // draw ground
        wattron(game_wnd, COLOR_PAIR(2));
        mvwhline(game_wnd, ground_y, 0, '_', screen_w-2);
        wattroff(game_wnd, COLOR_PAIR(2));

        // handle player vertical movement (very simple physics)
        if (!game_over) {
            if (player.up) {
                // jump: move up for a short time then fall
                if (player.air_time < player.max_air_time) {
                    // move sprite up 1 row every few ticks
                    if (tick % 2 == 0) {
                        for (auto &p : player.pos) p.y -= 1;
                        for (auto &p : player.crouch_pos) p.y -= 1;
                    }
                } else {
                    // reached peak, start descending
                    player.up = false;
                }
                player.air_time++;
            } else {
                // fall back to ground if above ground
                // ensure bottom-most y equals ground (player was set relative)
                int current_bottom = player.pos.back().y;
                int target_bottom = ground_y - 0; // allow sprite bottom at ground_y
                if (current_bottom < target_bottom) {
                    if (tick % 2 == 0) {
                        for (auto &p : player.pos) p.y += 1;
                        for (auto &p : player.crouch_pos) p.y += 1;
                    }
                } else {
                    // landed
                    player.air_time = 0;
                }
            }
            // if no crouch key pressed, stand
            if (ch != 's' && ch != KEY_DOWN) player.stand();
        }

        // spawn obstacles periodically
        if (!game_over) {
            spawn_ticks++;
            if (spawn_ticks >= spawn_interval) {
                spawn_ticks = 0;
                // randomize what to spawn
                int r = std::rand() % 6;
                if (r < 4) { // spawn cactus
                    Cactus c(screen_w - 6, ground_y);
                    cactuses.push_back(c);
                } else { // spawn bird at random height
                    int bh = birdheight(rng);
                    Bird b(screen_w - 6, bh);
                    birds.push_back(b);
                }
            }
        }

        // update & draw obstacles
        for (auto it = cactuses.begin(); it != cactuses.end(); ) {
            it->update();
            if (!game_over) it->draw(game_wnd);
            if (it->offscreen(0)) it = cactuses.erase(it);
            else ++it;
        }
        for (auto it = birds.begin(); it != birds.end(); ) {
            it->update();
            if (!game_over) it->draw(game_wnd);
            if (it->offscreen(0)) it = birds.erase(it);
            else ++it;
        }

        // draw player
        player.updateBounds();
        if (!game_over) player.draw(game_wnd);

        // collision detection
        player.updateBounds();
        for (const auto &c : cactuses) {
            if (isCollided(player.bounds, c.bounds)) {
                game_over = true;
            }
        }
        for (const auto &b : birds) {
            if (isCollided(player.bounds, b.bounds)) {
                game_over = true;
            }
        }

        // score
        if (!game_over) {
            if (tick % 4 == 0) score++;
            player.score = score;
            if (score > max_score) max_score = score;
        }

        // HUD
        wattron(game_wnd, A_BOLD);
        mvwprintw(game_wnd, 0, 1, "SCORE: %d  HIGH: %d", score, max_score);
        wattroff(game_wnd, A_BOLD);

        if (game_over) {
            mvwprintw(game_wnd, 4, 10, "=== GAME OVER ===");
            mvwprintw(game_wnd, 6, 8, "Press 'r' to retry or 'q' to quit");
        }

        wrefresh(game_wnd);
        usleep(30000); // ~30ms per frame

        tick++;
        // increase difficulty a bit
        if (tick % 1000 == 0 && spawn_interval > 12) spawn_interval -= 2;
    }

    // unreachable
    return true;
}

void close() {
    if (game_wnd) delwin(game_wnd);
    endwin();
}