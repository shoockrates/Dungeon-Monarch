#include "../include/Renderer.h"
#include "../include/UserInput.h"
#include "../include/Room.h"
#include "../include/Game.h"
#include <iostream>
#include <cstdlib>
#include <string>

int main() {

    Game* game = nullptr;
    game = new Game();

    game->run();

    delete game;
	return 0;
}