#include "Display.h"
#include <iostream>

Display::Display(const std::string& title, int width, int height, bool fullscreen)
    : m_window(nullptr), m_renderer(nullptr), m_width(width), m_height(height), m_fullscreen(fullscreen)
{
    m_window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        fullscreen ? SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS : SDL_WINDOW_SHOWN
    );
    if (!m_window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Failed to create SDL_Window");
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        throw std::runtime_error("Failed to create SDL_Renderer");
    }

    if (fullscreen) {
        SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
    }
}

Display::~Display() {
    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window) SDL_DestroyWindow(m_window);
}

void Display::setFullscreen(bool fullscreen) {
    m_fullscreen = fullscreen;
    if (m_window) {
        SDL_SetWindowFullscreen(m_window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
    }
} 