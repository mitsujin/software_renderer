#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include "Renderer.h"

// Function to create and initialize SDL window and renderer
bool createWindow(SDL_Window** window, SDL_Renderer** renderer, const char* title, int width, int height) {
    // Initialize SDL
    // Create window
    *window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );

    if (!*window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(*window);
        return false;
    }

    SDL_SetWindowFullscreen(*window, SDL_WINDOW_FULLSCREEN);

    return true;
}

bool g_quit = false;
std::unique_ptr<Renderer> g_renderer;

void processInput();
void update();
void render();

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    int width = displayMode.w;
    int height = displayMode.h;

    // Create window and renderer
    if (!createWindow(&window, &renderer, "SoftRenderer - Hello World", width, height)) {
        return 1;
    }

    // Create our software renderer
    g_renderer = std::make_unique<Renderer>(width, height, renderer);

    // Main loop
    g_quit = false;
    SDL_Event event;

    while (!g_quit) {

        processInput();
        update();
        render();

    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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

}

void render() {

    // Clear our buffer with dark blue
    g_renderer->clear(Renderer::createColor(0, 0, 0));
    
    g_renderer->drawGrid(10, 0xFF333333);
    g_renderer->drawRect(100, 100, 300, 200, 0xFFFFFFFF);
    
    // Present our buffer to the screen
    g_renderer->present();
}