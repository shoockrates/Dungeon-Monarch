#include "../../include/menuSystem/LoseWindow.h"
#include "../../include/Room.h"

LooseWindow::LooseWindow(SDL_Renderer* ren, SaveManager *sm)
    : Menu(ren, false, sm) {}

void LooseWindow::rebuildButtons() {
    buttons.clear();
    float centerX = Room::getWidth() * Room::getTileSize() / 2.0f - 150.0f;
    float centerY = Room::getHeight() * Room::getTileSize() / 2.0f;

    buttons.emplace_back(centerX, centerY - 100.0f, 300.0f, 50.0f, "You died.", false);
    buttons.emplace_back(centerX, centerY, 300.0f, 50.0f, "Load");
    buttons.emplace_back(centerX, centerY + 100.0f, 300.0f, 50.0f, "Quit");
}
