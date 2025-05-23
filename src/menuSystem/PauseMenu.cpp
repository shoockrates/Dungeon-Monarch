#include "../../include/menuSystem/PauseMenu.h"
#include "../../include/Room.h"

PauseMenu::PauseMenu(SDL_Window* win, SDL_Renderer* ren)
    : Menu(win, ren, true) {}


void PauseMenu::rebuildButtons() {
    buttons.clear();
    float centerX = Room::getWidth() * Room::getTileSize() / 2.0f - 150.0f;
    float centerY = Room::getHeight() * Room::getTileSize() / 2.0f;

    buttons.emplace_back(centerX, centerY - 150.0f, 300.0f, 50.0f, "Resume");
    buttons.emplace_back(centerX, centerY - 50.0f, 300.0f, 50.0f, "Save");
    buttons.emplace_back(centerX, centerY + 50.0f, 300.0f, 50.0f, "Load");
    buttons.emplace_back(centerX, centerY + 150.0f, 300.0f, 50.0f, "Quit");
}
