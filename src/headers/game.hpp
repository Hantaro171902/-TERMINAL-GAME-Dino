#pragma once

#include "ansi_renderer.hpp"

bool isCollided(rect a, rect b);
int init();
bool run(int& max_score);
void close();