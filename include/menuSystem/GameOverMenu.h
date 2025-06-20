#pragma once
#include "Menu.h"
#include "../SaveManager.h"

class GameOverMenu : public Menu {
private:
    bool isWin;
public:
    GameOverMenu(SDL_Renderer* ren, SaveManager *sm, bool isWin);
    virtual ~GameOverMenu() {}

    void rebuildButtons() override;
};
