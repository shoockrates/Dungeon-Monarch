#include "../include/Renderer.h"
#include "../include/UserInput.h"
#include "../include/Room.h"
#include "../include/Game.h"
#include <iostream>
#include <cstdlib>
#include <string>

int main() {

    std::string playerName;
    std::cout << "Please enter your player name: ";

    // Read the entire line of input, allowing for names with spaces
    std::getline(std::cin, name);

    // Simple validation: ensure the name is not empty
    while (playerName.empty()) {
        std::cout << "Name cannot be empty. Please try again: ";
        std::getline(std::cin, playerName);
    } 
    Game* game = nullptr;
    game = new Game();

    game->run();

    delete game;
	return 0;
}
