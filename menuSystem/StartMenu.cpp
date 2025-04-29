// StartMenu.cpp

#include "StartMenu.h"

StartMenu::StartMenu(SDL_Window* win, SDL_Renderer* ren, int* w, int* h)
    : Menu(win, ren, w, h) {}


void StartMenu::rebuildButtons() {
    buttons.clear();
    buttons.emplace_back(*width / 2 - 150.0f, *height / 2 - 100.0f, 300.0f, 50.0f, "Start Game");
    buttons.emplace_back(*width / 2 - 150.0f, *height / 2, 300.0f, 50.0f, "Options");
    buttons.emplace_back(*width / 2 - 150.0f, *height / 2 + 100.0f, 300.0f, 50.0f, "Quit");
}
