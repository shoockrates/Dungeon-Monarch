// PauseMenu.h
#pragma once
#include "Menu.h"

class PauseMenu : public Menu {
public:
    PauseMenu(SDL_Window* window, SDL_Renderer* renderer, int* width, int* height);
    virtual ~PauseMenu() {}

private:
    void rebuildButtons() override;
};
