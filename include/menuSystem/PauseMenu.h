#pragma once
#include "Menu.h"
#include "../SaveManager.h"

class PauseMenu : public Menu {
public:
    PauseMenu(SDL_Renderer* ren, SaveManager *sm);
    virtual ~PauseMenu() {}

private:
    void rebuildButtons() override;
};
