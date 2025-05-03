// PauseMenu.h
#pragma once
#include "Menu.h"

class PauseMenu : public Menu {
public:
    PauseMenu(SDL_Window* window, SDL_Renderer* renderer);
    virtual ~PauseMenu() {}

private:
    void rebuildButtons() override;
};
