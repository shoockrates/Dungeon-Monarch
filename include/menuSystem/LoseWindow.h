#pragma once
#include "Menu.h"
#include "../SaveManager.h"

class LooseWindow : public Menu {
public:
    LooseWindow(SDL_Renderer* ren, SaveManager *sm);
    virtual ~LooseWindow() {}

    void rebuildButtons() override;
};
