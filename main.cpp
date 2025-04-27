#include "Renderer.h"
#include "UserInput.h"
#include "Room.h"
#include "menuSystem.h"
#include <iostream>
#include <cstdlib>
#include <string>

int width = 1000;
int height = 500;

int main() {

	SDL_Window* window = SDL_CreateWindow("Game Menu", width, height, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

	if (loadMenu(window, renderer, &width, &height)){
		std::cout << "Player started the game." << std::endl;
	} else {
		std::cout << "Player quit the game." << std::endl;
	}

	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	TTF_Quit();
    SDL_Quit();

	return 0;
}