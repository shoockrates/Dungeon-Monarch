#include "../../include/menuSystem/UpgradeMenu.h"
#include "../../include/Room.h"

UpgradeMenu::UpgradeMenu(SDL_Renderer* ren, SaveManager* sm)
    : Menu(ren, true, sm) {
}

void UpgradeMenu::rebuildButtons() {
    buttons.clear();
    float centerX = Room::getWidth() * Room::getTileSize() / 2.0f - 150.0f;
    float centerY = Room::getHeight() * Room::getTileSize() / 2.0f;

    buttons.emplace_back(centerX, centerY - 75.0f, 300.0f, 50.0f, "Upgrade attack");
    buttons.emplace_back(centerX, centerY + 75.0f, 300.0f, 50.0f, "Upgrade health");
}