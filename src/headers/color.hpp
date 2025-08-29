#pragma once
#include <string>
#include <ncurses.h>

// ANSI color constants for Linux/Unix
enum TextColor {
    COLOR_DEFAULT = 1, // Start at 1 to match ncurses pair indexing
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_GRAY,
    COLOR_CYAN,
    COLOR_WHITE,
    COLOR_BG_GREEN,
    COLOR_BRIGHT_RED,
    COLOR_BRIGHT_GREEN,
    COLOR_BRIGHT_YELLOW,
    COLOR_BRIGHT_BLUE,
    COLOR_BRIGHT_MAGENTA,
    COLOR_BRIGHT_CYAN,
    COLOR_BRIGHT_WHITE
};

void initColors();