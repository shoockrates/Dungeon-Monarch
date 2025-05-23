#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <string>
#include <iostream>

#include "../UserInput.h"

struct Button {
    SDL_FRect rect;
    std::string label;
    bool isHovered;
    SDL_Texture* texture;

    Button(float x, float y, float w, float h, const std::string& text)
        : label(text), isHovered(false), texture(nullptr) {

            rect.x = x;
            rect.y = y;
            rect.w = w;
            rect.h = h;
        }
};

class Menu {
public:
    Menu(SDL_Window* window, SDL_Renderer* renderer, bool isPauseMenu);
    virtual ~Menu();

    int run();

protected:
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Color textColor;
    SDL_Color hoverColor;
    TTF_Font* font;

    bool running;
    bool inMenu;
    bool isPauseMenu;

    UserInput userInput;

    std::vector<Button> buttons;

    bool isMouseOver(SDL_FRect rect, int x, int y);
    void renderButton(Button& button);
    void handleEvents();
    void updateButtons();
    void cleanUp();

    virtual void rebuildButtons();
};
