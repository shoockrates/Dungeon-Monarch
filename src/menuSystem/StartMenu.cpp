// StartMenu.cpp

#include "../../include/menuSystem/StartMenu.h"
#include "../../include/Room.h"

StartMenu::StartMenu(SDL_Window* win, SDL_Renderer* ren)
    : Menu(win, ren, false) {}


void StartMenu::rebuildButtons() {
    buttons.clear();
    buttons.emplace_back(Room::getWidth() * Room::getTileSize() / 2 - 150.0f, Room::getHeight() * Room::getTileSize() / 2 - 100.0f, 300.0f, 50.0f, "Start Game");
    buttons.emplace_back(Room::getWidth() * Room::getTileSize() / 2 - 150.0f, Room::getHeight() * Room::getTileSize() / 2, 300.0f, 50.0f, "Options");
    buttons.emplace_back(Room::getWidth() * Room::getTileSize() / 2 - 150.0f, Room::getHeight() * Room::getTileSize() / 2 + 100.0f, 300.0f, 50.0f, "Quit");
}
