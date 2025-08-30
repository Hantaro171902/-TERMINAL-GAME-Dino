#pragma once

struct vec2i
{
    int x;
    int y;
};

struct rect
{
    vec2i offset;
    vec2i bounds;

    int top() { return offset.y; }
    int bot() { return offset.y + bounds.y; }
    int left() { return offset.x; }
    int right() { return offset.x + bounds.x; }

    int width() { return bounds.x; }
    int height() { return bounds.y; }
};


bool isCollided(rect a, rect b);
int init();
bool run(int& max_score);
void close();