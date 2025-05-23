#pragma once
#include "Menu.h"

class StartMenu : public Menu {
public:
    StartMenu(SDL_Window* window, SDL_Renderer* renderer);
    virtual ~StartMenu() {}

    void rebuildButtons() override;
};
