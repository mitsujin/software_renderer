#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include "Renderer.h"

// Function to create and initialize SDL window and renderer
bool createWindow(SDL_Window** window, SDL_Renderer** renderer, const char* title, int width, int height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    *window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN
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

    // Create window and renderer
    if (!createWindow(&window, &renderer, "SoftRenderer - Hello World", 800, 600)) {
        return 1;
    }

    // Create our software renderer
    g_renderer = std::make_unique<Renderer>(800, 600, renderer);

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
    g_renderer->clear(Renderer::createColor(255, 0, 50));
    
    // Draw a white rectangle
    uint32_t white = Renderer::createColor(255, 255, 255);
    g_renderer->drawRect(350, 250, 100, 100, white);
    
    // Draw some lines
    uint32_t red = Renderer::createColor(255, 0, 0);
    uint32_t green = Renderer::createColor(0, 255, 0);
    uint32_t blue = Renderer::createColor(0, 0, 255);
    
    g_renderer->drawLine(100, 100, 200, 200, red);
    g_renderer->drawLine(200, 100, 300, 200, green);
    g_renderer->drawLine(300, 100, 400, 200, blue);
    
    // Present our buffer to the screen
    g_renderer->present();
}