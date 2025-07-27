#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include "Renderer.h"
#include "Display.h"

bool g_quit = false;
std::unique_ptr<Renderer> g_renderer;
std::unique_ptr<Display> g_display;

void processInput();
void update();
void render();

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    int width = displayMode.w;
    int height = displayMode.h;

    try {
        g_display = std::make_unique<Display>("SoftRenderer - Hello World", width, height, true);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        SDL_Quit();
        return 1;
    }

    g_renderer = std::make_unique<Renderer>(width, height, g_display->getRenderer());

    g_quit = false;
    while (!g_quit) {
        processInput();
        update();
        render();
    }

    g_renderer.reset();
    g_display.reset();
    SDL_Quit();
    std::cout << "SoftRenderer Hello World completed successfully!" << std::endl;
    return 0;
}

void processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                g_quit = true;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    g_quit = true;
                }
                break;
            default:
                break;
        }
    }
}

void update() {
    // Game logic or animation updates here
}

void render() {
    g_renderer->clear(Renderer::createColor(0, 0, 0));
    g_renderer->drawGrid(10, 0xFF333333);
    g_renderer->drawRect(100, 100, 300, 200, 0xFFFFFFFF);
    g_renderer->present();
}