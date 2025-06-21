#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <string>
#include <iostream>

#include "../UserInput.h"
#include "../SaveManager.h"

struct Button {
    SDL_FRect rect;
    std::string label;
    bool isHovered;
    bool canBeHovered;
    SDL_Texture* texture;

    Button(float x, float y, float w, float h, const std::string& text, bool hover = true)
        : label(text), isHovered(false), texture(nullptr), canBeHovered(hover) {

            rect.x = x;
            rect.y = y;
            rect.w = w;
            rect.h = h;
        }
};

class Menu {
public:
    Menu(SDL_Renderer* ren, bool pause, SaveManager *sm);
    virtual ~Menu();

    int run();

protected:
    SDL_Renderer* renderer;

    SDL_Color textColor;
    SDL_Color hoverColor;
    TTF_Font* font;

    bool running;
    bool inMenu;
    bool isPauseMenu;

    int returnValue;

    UserInput userInput;
    SaveManager *saveManager;

    std::vector<Button> buttons;

    bool isMouseOver(SDL_FRect rect, int x, int y);
    void renderButton(Button& button);
    void handleEvents();
    void updateButtons();
    void cleanUp();

    virtual void rebuildButtons();
};
