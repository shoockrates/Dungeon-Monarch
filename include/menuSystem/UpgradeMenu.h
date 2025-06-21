#pragma once
#include "Menu.h"
#include "../SaveManager.h"

class UpgradeMenu : public Menu {
public:
    UpgradeMenu(SDL_Renderer* ren, SaveManager* sm);
    virtual ~UpgradeMenu() {}

private:
    void rebuildButtons() override;
};