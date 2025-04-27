#include <iostream>
#include <cstdlib>
#include <string>

#include <SDL3_ttf/SDL_ttf.h>

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

/**
 * @brief Opens main game menu
 * 
 * @return
 * 1 if started the game;
 * 0 if quit
 */
int loadMenu(SDL_Window* window, SDL_Renderer* renderer, int *width, int *height);

bool isMouseOver(SDL_FRect rect, int x, int y);
void renderButton(SDL_Renderer* renderer, Button& button, TTF_Font* font, SDL_Color textColor, SDL_Color hoverColor);
