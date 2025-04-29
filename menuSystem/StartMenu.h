// StartMenu.h
#pragma once
#include "Menu.h"

class StartMenu : public Menu {
public:
    StartMenu(SDL_Window* window, SDL_Renderer* renderer, int* width, int* height);
    virtual ~StartMenu() {}

    void rebuildButtons() override;
};
