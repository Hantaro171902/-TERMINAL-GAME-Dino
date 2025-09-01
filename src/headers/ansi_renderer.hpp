#pragma once

#include "color.hpp"
#include <vector>
#include <string>

struct vec2i {
    int x, y;
};

struct rect {
    vec2i top_left;
    vec2i bounds;
    
    int left() const { return top_left.x; }
    int right() const { return bounds.x; }
    int top() const { return top_left.y; }
    int bot() const { return bounds.y; }
    int width() const { return bounds.x - top_left.x; }
    int height() const { return bounds.y - top_left.y; }
};

class ANSIRenderer {
public:
    ANSIRenderer(int width, int height);
    ~ANSIRenderer();
    
    void clear();
    void refresh();
    void drawChar(int x, int y, char ch, TextColor text_color = WHITE, TextColor bg_color = DEFAULT);
    void drawString(int x, int y, const std::string& str, TextColor text_color = WHITE, TextColor bg_color = DEFAULT);
    void drawLine(int x, int y, int length, char ch, TextColor text_color = WHITE, TextColor bg_color = DEFAULT);
    void drawBox(int x, int y, int width, int height, TextColor text_color = WHITE, TextColor bg_color = DEFAULT);
    void moveCursor(int x, int y);
    
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    
private:
    int m_width;
    int m_height;
    std::vector<std::vector<char>> m_buffer;
    std::vector<std::vector<TextColor>> m_text_colors;
    std::vector<std::vector<TextColor>> m_bg_colors;
    bool m_needs_refresh;
    
    void flushBuffer();
};
