#include "../../include/menuSystem/GameOverMenu.h"
#include "../../include/Room.h"

GameOverMenu::GameOverMenu(SDL_Renderer* ren, SaveManager *sm, bool win)
    : Menu(ren, false, sm), isWin(win) {}

void GameOverMenu::rebuildButtons() {
    buttons.clear();
    float centerX = Room::getWidth() * Room::getTileSize() / 2.0f - 150.0f;
    float centerY = Room::getHeight() * Room::getTileSize() / 2.0f;

    if (isWin) {
        buttons.emplace_back(centerX, centerY - 100.0f, 300.0f, 50.0f, "You win!", false);
        //buttons.emplace_back(centerX, centerY, 300.0f, 50.0f, "Play again");
    } else {
        buttons.emplace_back(centerX, centerY - 100.0f, 300.0f, 50.0f, "You died.", false);
        buttons.emplace_back(centerX, centerY, 300.0f, 50.0f, "Load");
    }
    buttons.emplace_back(centerX, centerY + 100.0f, 300.0f, 50.0f, "Quit");
}
