#pragma once

// ANSI color constants for Linux/Unix
enum TextColor {
    DEFAULT = 0,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    GRAY = 30,
    CYAN = 36,
    WHITE = 37,
    BG_BLACK = 40,
    BG_RED = 41,
    BG_GREEN = 42,
    BG_YELLOW = 43,
    BG_BLUE = 44,
    BG_MAGENTA = 45,
    BG_CYAN = 46,
    BG_WHITE = 47,
    BRIGHT_RED = 91,
    BRIGHT_GREEN = 92,
    BRIGHT_YELLOW = 93,
    BRIGHT_BLUE = 94,
    BRIGHT_MAGENTA = 95,
    BRIGHT_CYAN = 96,
    BRIGHT_WHITE = 97
};

// Game-specific color functions
void setTextColor(TextColor color);
void setBackgroundColor(TextColor bg_color);
void setTextAndBackground(TextColor text_color, TextColor bg_color);
void resetTextColor();
void clearScreen();
void moveCursor(int x, int y);
void hideCursor();
void showCursor();

// Game color constants
const TextColor GROUND_BG = BG_WHITE;
const TextColor GROUND_TEXT = GRAY;
const TextColor PLAYER_COLOR = WHITE;
const TextColor OBSTACLE_COLOR = WHITE;
const TextColor SCORE_COLOR = WHITE;
