#include "ansi_renderer.hpp"
#include <iostream>
#include <cstring>

ANSIRenderer::ANSIRenderer(int width, int height) 
    : m_width(width), m_height(height), m_needs_refresh(false) {
    
    // Initialize buffers
    m_buffer.resize(height, std::vector<char>(width, ' '));
    m_text_colors.resize(height, std::vector<TextColor>(width, DEFAULT));
    m_bg_colors.resize(height, std::vector<TextColor>(width, DEFAULT));
    
    // Setup terminal
    hideCursor();
    clearScreen();
}

ANSIRenderer::~ANSIRenderer() {
    showCursor();
    resetTextColor();
}

void ANSIRenderer::clear() {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            m_buffer[y][x] = ' ';
            m_text_colors[y][x] = DEFAULT;
            m_bg_colors[y][x] = DEFAULT;
        }
    }
    m_needs_refresh = true;
}

void ANSIRenderer::refresh() {
    if (m_needs_refresh) {
        flushBuffer();
        m_needs_refresh = false;
    }
}

void ANSIRenderer::drawChar(int x, int y, char ch, TextColor text_color, TextColor bg_color) {
    if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
        m_buffer[y][x] = ch;
        m_text_colors[y][x] = text_color;
        m_bg_colors[y][x] = bg_color;
        m_needs_refresh = true;
    }
}

void ANSIRenderer::drawString(int x, int y, const std::string& str, TextColor text_color, TextColor bg_color) {
    for (size_t i = 0; i < str.length(); i++) {
        drawChar(x + i, y, str[i], text_color, bg_color);
    }
}

void ANSIRenderer::drawLine(int x, int y, int length, char ch, TextColor text_color, TextColor bg_color) {
    for (int i = 0; i < length; i++) {
        drawChar(x + i, y, ch, text_color, bg_color);
    }
}

void ANSIRenderer::drawBox(int x, int y, int width, int height, TextColor text_color, TextColor bg_color) {
    // Draw top and bottom borders
    for (int i = 0; i < width; i++) {
        drawChar(x + i, y, '-', text_color, bg_color);
        drawChar(x + i, y + height - 1, '-', text_color, bg_color);
    }
    
    // Draw left and right borders
    for (int i = 0; i < height; i++) {
        drawChar(x, y + i, '|', text_color, bg_color);
        drawChar(x + width - 1, y + i, '|', text_color, bg_color);
    }
    
    // Draw corners
    drawChar(x, y, '+', text_color, bg_color);
    drawChar(x + width - 1, y, '+', text_color, bg_color);
    drawChar(x, y + height - 1, '+', text_color, bg_color);
    drawChar(x + width - 1, y + height - 1, '+', text_color, bg_color);
}

void ANSIRenderer::moveCursor(int x, int y) {
    ::moveCursor(x + 1, y + 1); // ANSI coordinates are 1-based
}

void ANSIRenderer::flushBuffer() {
    ::moveCursor(0, 0);
    
    TextColor current_text = DEFAULT;
    TextColor current_bg = DEFAULT;
    
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            // Only change colors if necessary
            if (m_text_colors[y][x] != current_text || m_bg_colors[y][x] != current_bg) {
                if (m_bg_colors[y][x] == DEFAULT) {
                    setTextColor(m_text_colors[y][x]);
                } else {
                    setTextAndBackground(m_text_colors[y][x], m_bg_colors[y][x]);
                }
                current_text = m_text_colors[y][x];
                current_bg = m_bg_colors[y][x];
            }
            
            std::cout << m_buffer[y][x];
        }
        
        if (y < m_height - 1) {
            std::cout << std::endl;
        }
    }
    
    resetTextColor();
}
