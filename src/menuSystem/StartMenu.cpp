#include "../../include/menuSystem/StartMenu.h"
#include "../../include/Room.h"

StartMenu::StartMenu(SDL_Window* win, SDL_Renderer* ren)
    : Menu(win, ren, false) {}

void StartMenu::rebuildButtons() {
    buttons.clear();
    float centerX = Room::getWidth() * Room::getTileSize() / 2.0f - 150.0f;
    float centerY = Room::getHeight() * Room::getTileSize() / 2.0f;

    buttons.emplace_back(centerX, centerY - 100.0f, 300.0f, 50.0f, "Start Game");
    buttons.emplace_back(centerX, centerY, 300.0f, 50.0f, "Load");
    buttons.emplace_back(centerX, centerY + 100.0f, 300.0f, 50.0f, "Quit");
}
