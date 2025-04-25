#include "Renderer.h"
#include "UserInput.h"
#include "Room.h"
#include "menuSystem.h"
#include <iostream>
#include <cstdlib>
#include <string>

int main() {
	if (gameMenu()){
		std::cout << "Player started the game." << std::endl;
	}
	return 0;
}