#include "Game.h"

Game::Game(){
	try {
		testSprite = renderer.loadSprite("assets/test.bmp");
	}
	catch (const std::exception& e) {
		SDL_Log("Sprite loading failed: %s", e.what());
		running = false;
	}
}

Game::~Game() {
	SDL_DestroyTexture(testSprite);
	SDL_Quit();
}

void Game::run(){
	frameStart = SDL_GetTicks();
	userInput.collectInput();

	if (userInput.shouldQuit()) {
		running = false;
	}
	renderer.drawRoomTiled(testSprite, room.getWidth(), room.getHeight(), room.getTileSize());
	renderer.present();
	frameTime = SDL_GetTicks() - frameStart;

	if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
	}
}
void Game::loadMenu() {};
void Game::enterRoom(int roomId) {};
void Game::killEntity(int entityId) {};

void Game::handleEvents() {

}


bool Game::getRunning() const { return running; }
UserInput Game::getUserInput() const { return userInput; }