#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <vector>

class Renderer {
public:
    Renderer(int width, int height, SDL_Renderer* sdlRenderer);
    ~Renderer();

    // Buffer management
    void clear(uint32_t color);
    void setPixel(int x, int y, uint32_t color);
    uint32_t getPixel(int x, int y) const;
    
    // Drawing functions
    void drawRect(int x, int y, int width, int height, uint32_t color);
    void drawLine(int x1, int y1, int x2, int y2, uint32_t color);
    void drawGrid(int spacing, uint32_t color);
    
    // Buffer operations
    void present();
    void resize(int width, int height);

    // Getters
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    uint32_t* getBuffer() { return m_colorBuffer.data(); }
    const uint32_t* getBuffer() const { return m_colorBuffer.data(); }
    
    // Color utilities
    static uint32_t createColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    static void extractColor(uint32_t color, uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a);

private:
    std::vector<uint32_t> m_colorBuffer;
    SDL_Texture* m_texture;
    SDL_Renderer* m_sdlRenderer;
    int m_width;
    int m_height;
    
    bool isValidPixel(int x, int y) const;
}; 