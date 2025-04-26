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

    game->run();

    delete game;
	return 0;
}