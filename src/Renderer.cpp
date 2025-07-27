#include "Renderer.h"
#include <algorithm>
#include <cmath>

Renderer::Renderer(int width, int height, SDL_Renderer* sdlRenderer) 
    : m_width(width), m_height(height), m_texture(nullptr), m_sdlRenderer(sdlRenderer) {
    m_colorBuffer.resize(width * height);

    m_texture = SDL_CreateTexture(
        m_sdlRenderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        m_width,
        m_height
    );
    clear(0xFF000000); // Clear with black
}

Renderer::~Renderer() {
    if (m_texture) {
        SDL_DestroyTexture(m_texture);
    }
}

void Renderer::clear(uint32_t color) {
    std::fill(m_colorBuffer.begin(), m_colorBuffer.end(), color);
}

void Renderer::setPixel(int x, int y, uint32_t color) {
    if (!isValidPixel(x, y)) return;
    
    int index = y * m_width + x;
    m_colorBuffer[index] = color;
}

uint32_t Renderer::getPixel(int x, int y) const {
    if (!isValidPixel(x, y)) return 0;
    
    int index = y * m_width + x;
    return m_colorBuffer[index];
}

void Renderer::drawRect(int x, int y, int width, int height, uint32_t color) {
    for (int py = y; py < y + height; ++py) {
        for (int px = x; px < x + width; ++px) {
            setPixel(px, py, color);
        }
    }
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, uint32_t color) {
    // Bresenham's line algorithm
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    
    int x = x1, y = y1;
    
    while (true) {
        setPixel(x, y, color);
        
        if (x == x2 && y == y2) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

void Renderer::present() {
    if (!m_sdlRenderer) return;
    
    // Update texture with our buffer
    SDL_UpdateTexture(m_texture, nullptr, m_colorBuffer.data(), m_width * sizeof(uint32_t));
    
    // Render the texture
    SDL_RenderCopy(m_sdlRenderer, m_texture, nullptr, nullptr);

    SDL_RenderPresent(m_sdlRenderer);
}

void Renderer::resize(int width, int height) {
    m_width = width;
    m_height = height;
    m_colorBuffer.resize(width * height);
    
    // Recreate texture
    if (m_texture) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
}

uint32_t Renderer::createColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return (static_cast<uint32_t>(a) << 24) |
           (static_cast<uint32_t>(r) << 16) |
           (static_cast<uint32_t>(g) << 8) |
           static_cast<uint32_t>(b);
}

void Renderer::extractColor(uint32_t color, uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a) {
    a = static_cast<uint8_t>((color >> 24) & 0xFF);
    r = static_cast<uint8_t>((color >> 16) & 0xFF);
    g = static_cast<uint8_t>((color >> 8) & 0xFF);
    b = static_cast<uint8_t>(color & 0xFF);
}

bool Renderer::isValidPixel(int x, int y) const {
    return x >= 0 && x < m_width && y >= 0 && y < m_height;
} 