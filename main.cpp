#include "Renderer.h"
#include "UserInput.h"
#include "Room.h"
#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <string>

int main() {

    Game* game = nullptr;
    game = new Game();

    while (game->getRunning()) {

        game->run();
        //game->getUserInput().collectUserInput();
        


    }

    /*
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
    */
    delete game;
	return 0;
}