#include "Renderer.h"
#include "UserInput.h"
#include "Room.h"
#include <iostream>
#include <cstdlib>
#include <string>

#include <SDL3_ttf/SDL_ttf.h>

const int WIDTH = 1000;
const int HEIGHT = 1000;

bool isMouseOver(SDL_Rect rect, int x, int y) {
    return (x >= rect.x && x <= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h);
}

int main() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0) {
        std::cerr << "SDL Init Failed: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Game Menu", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    TTF_Font* font = TTF_OpenFont("assets/font.ttf", 48);
    if (!font) {
        std::cerr << "Font load failed." << "\n";
        return 1;
    }

    SDL_Color white = {255, 255, 255};
    SDL_Color red = {255, 0, 0};

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Start Game", 10, white);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect buttonRect = {WIDTH / 2 - 100, HEIGHT / 2 - 25, 200, 50};
    SDL_FRect buttonFRect = {WIDTH / 2 - 100, HEIGHT / 2 - 25, 200, 50};
    bool running = true;
    bool inMenu = true;

    SDL_Event e;
    while (running) {
        SDL_GetMouseState(nullptr, nullptr);
        float mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
                running = false;

            if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN && inMenu &&
                isMouseOver(buttonRect, mouseX, mouseY)) {
                std::cout << "Starting Game...\n";
                inMenu = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (inMenu) {
            // Draw button background
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderFillRect(renderer, &buttonFRect);

            // Hover effect
            if (isMouseOver(buttonRect, mouseX, mouseY)) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Change color on hover (Red)
                SDL_RenderFillRect(renderer, &buttonFRect);
            }

            // Draw text
            SDL_RenderTexture(renderer, textTexture, nullptr, &buttonFRect);
        } else {
            // HERE GOES THE GAME
            // Draw game screen
            SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);
            SDL_RenderClear(renderer);
        }

        SDL_RenderPresent(renderer);
    }

	return 0;
}