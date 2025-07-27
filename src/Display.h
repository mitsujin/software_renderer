#pragma once

#include <SDL2/SDL.h>
#include <string>

class Display {
public:
    Display(const std::string& title, int width, int height, bool fullscreen = true);
    ~Display();

    SDL_Renderer* getRenderer() const { return m_renderer; }
    SDL_Window* getWindow() const { return m_window; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    void setFullscreen(bool fullscreen);

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    int m_width;
    int m_height;
    bool m_fullscreen;
}; 