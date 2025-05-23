#pragma once
#include "Menu.h"
#include "../SaveManager.h"

class StartMenu : public Menu {
public:
    StartMenu(SDL_Renderer* ren, SaveManager *sm);
    virtual ~StartMenu() {}

    void rebuildButtons() override;
};
