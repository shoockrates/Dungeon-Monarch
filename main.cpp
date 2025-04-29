#include <SDL3/SDL.h>
#include "menuSystem/StartMenu.h"
#include "menuSystem/PauseMenu.h"

int main() {
    int width = 800;
    int height = 600;

	SDL_Window* window = SDL_CreateWindow("Dungeon Monarch", width, height, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    StartMenu startMenu(window, renderer, &width, &height);
    
    if (startMenu.run()) {
        std::cout << "Player pressed start game" << std::endl;
    } else {
        std::cout << "Player closed the game" << std::endl;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}