#include "Renderer.h"
#include "UserInput.h"
#include "Room.h"
#include <iostream>
#include <cstdlib>
#include <string>

int main() {
    std::string name_of_a_character = "";

    std::cout << "Enter the name of your character: ";
    std::cin >> name_of_a_character;

    std::string command = "python sendData.py " + name_of_a_character;
    int status = std::system(command.c_str());

    if (status == 0) {
        std::cout << "Successfully inserted " << name_of_a_character << std::endl;
    }

    if (status == 1) {
        std::cout << "Error executing Python script" << std::endl;
    }

    if (status == 2) {
        std::cout << "Error: The name already exists in the database" << std::endl;
    }
	Room room1(1, false, true);
	Renderer renderer(room1.getWidth(), room1.getHeight(), room1.getTileSize());
	UserInput input;
    SDL_Texture* testSprite = nullptr;
    try {
        testSprite = renderer.loadSprite("assets/test.bmp");
    }
    catch (const std::exception& e) {
        SDL_Log("Sprite loading failed: %s", e.what());
        return -1;
    }
    bool running = true;
    while (running) {
        input.collectUserInput();
        if (input.shouldQuit()) {
            running = false;
            continue;
        }
        SDL_SetRenderDrawColor(renderer.getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer.getRenderer());
        renderer.drawRoomTiled(testSprite, room1.getWidth(), room1.getHeight(), room1.getTileSize());
        renderer.present();
    }
    SDL_DestroyTexture(testSprite);
    SDL_Quit();

	return 0;
}