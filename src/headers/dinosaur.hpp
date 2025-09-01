#pragma once 

#include <string>
#include <vector>
#include "game.hpp"
#include "ansi_renderer.hpp"

struct Player {
    std::vector<vec2i> pos;
    std::string disp_char{  "       ____ "
                            "      /0___}"
                            ",     ||    "
                            "|\\   / |    "
                            "| \\_/  =    "
                            " \\     |    "
                            "  \\ _  /    "
                            "  |/ [\\     "
                            "__[\\_______"};

    std::vector<vec2i> crouch_pos;

    std::string crouch_disp_char{",         ____ "
                                "|\\_______/0___}"
                                " \\       /     "
                                "  \\  _  /=     "
                                "   |/ [\\       "
                                "___[\\__________"};
    bool crouched;
    bool up;

    int air_time;
    int max_air_time;

    int score;

    rect bounds;
};

void initPlayerPosition(class ANSIRenderer *renderer, Player *player);
void clearPlayerPosition(class ANSIRenderer *renderer, Player *player);
void movePlayerUp(class ANSIRenderer *renderer, Player *player);
void movePlayerDown(class ANSIRenderer *renderer, Player *player);
void crouchPlayer(class ANSIRenderer *renderer, Player *player);
void playerFeetAnimation(class ANSIRenderer *renderer, Player *player);
// void playerDead();
