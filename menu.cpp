#include "Renderer.h"
#include "UserInput.h"
#include "Room.h"
#include <iostream>
#include <cstdlib>
#include <string>

#include <SDL3_ttf/SDL_ttf.h>

const int WIDTH = 1000;
const int HEIGHT = 1000;

struct Button {
    SDL_FRect rect;
    SDL_Texture* texture;
    std::string label;
    bool isHovered = false;

    Button(int x, int y, int w, int h, const std::string& lbl) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        texture = nullptr;
        label = lbl;
    }
};

bool isMouseOver(SDL_FRect rect, int x, int y) {
    return (x >= rect.x && x <= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h);
}

void renderButton(SDL_Renderer* renderer, Button& button, TTF_Font* font, SDL_Color textColor, SDL_Color hoverColor) {
    // Draw button background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer, &button.rect);

    // Hover effect (change color on hover)
    if (button.isHovered) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
        SDL_RenderFillRect(renderer, &button.rect);
    }

    // Render button text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, button.label.c_str(), button.label.size(), textColor);
    if (!textSurface) return;

    // Create texture from surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Get text size
    int textW = textSurface->w;
    int textH = textSurface->h;
    SDL_DestroySurface(textSurface);

    // Set destination rect to center text in the button
    SDL_FRect dstFRect;
    dstFRect.w = textW;
    dstFRect.h = textH;
    
    // Center the text inside the button rect
    dstFRect.x = button.rect.x + (button.rect.w - textW) / 2;
    dstFRect.y = button.rect.y + (button.rect.h - textH) / 2;

    // Render text
    SDL_RenderTexture(renderer, textTexture, nullptr, &dstFRect);

    // Free old texture if needed
    if (button.texture) SDL_DestroyTexture(button.texture);
    button.texture = textTexture; // save the new texture for cleanup
}

int main() {

    if (SDL_Init(SDL_INIT_VIDEO) == false || TTF_Init() == false) {
        std::cerr << "SDL Init Failed: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Game Menu", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    TTF_Font* font = TTF_OpenFont("assets/font.ttf", 48);
    if (!font) {
        std::cerr << "Font load failed." << endl;
        return 1;
    }

    SDL_Color white = {255, 255, 255};
    SDL_Color hoverColor = {255, 255, 255, 100}; // white with some transparency

    bool running = true;
    bool inMenu = true;

    std::vector<Button> buttons;
    buttons.emplace_back(WIDTH / 2 - 150.0f, HEIGHT / 2 - 100.0f, 300.0f, 50.0f, "Start Game");
    buttons.emplace_back(WIDTH / 2 - 150.0f, HEIGHT / 2, 300.0f, 50.0f, "Options");
    buttons.emplace_back(WIDTH / 2 - 150.0f, HEIGHT / 2 + 100.0f, 300.0f, 50.0f, "Quit");

    int width = WIDTH;
    int height = HEIGHT;

    int newWidth, newHeight;
    SDL_Event e;
    while (running) {
        SDL_GetMouseState(nullptr, nullptr);
        float mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // checks if window size changed and adapts
        SDL_GetWindowSize(window, &newWidth, &newHeight);
        if (newWidth != width || newHeight != height) {
            width = newWidth;
            height = newHeight;
            for(int i = 0; i < 3; ++i) {
                buttons.pop_back();
            }
            buttons.emplace_back(width / 2 - 150.0f, height / 2 - 100.0f, 300.0f, 50.0f, "Start Game");
            buttons.emplace_back(width / 2 - 150.0f, height / 2, 300.0f, 50.0f, "Options");
            buttons.emplace_back(width / 2 - 150.0f, height / 2 + 100.0f, 300.0f, 50.0f, "Quit");
        }

        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_EVENT_QUIT)
                running = false;

            if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN && inMenu) {
                for (size_t i = 0; i < buttons.size(); ++i) {
                    if (isMouseOver(buttons[i].rect, mouseX, mouseY)) {
                        if (buttons[i].label == "Start Game") {
                            std::cout << "Starting Game...\n";
                            inMenu = false;  // Transition to the game
                        } else if (buttons[i].label == "Options") {
                            std::cout << "Opening Options...\n";
                        } else if (buttons[i].label == "Quit") {
                            running = false;  // Quit the game
                        }
                    }
                }
            }

            SDL_Delay(16);
        }

        // Check if mouse is hovering over each button
        for (size_t i = 0; i < buttons.size(); ++i) {
            buttons[i].isHovered = isMouseOver(buttons[i].rect, mouseX, mouseY);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (inMenu) {
            for (size_t i = 0; i < buttons.size(); ++i) {
                renderButton(renderer, buttons[i], font, white, hoverColor);
            }
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