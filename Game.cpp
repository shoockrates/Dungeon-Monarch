#include "Game.h"


//Current images for testing and can be changed
Game::Game(){
	try {
		sprites.tileTexture = renderer.loadSprite("assets/test.bmp");
		sprites.playerTexture = renderer.loadSprite("assets/knight.bmp");
	}
	catch (const std::exception& e) {
		SDL_Log("Sprite loading failed: %s", e.what());
		running = false;
	}
}

Game::~Game() {
	SDL_DestroyTexture(sprites.tileTexture);
	SDL_DestroyTexture(sprites.playerTexture);
	SDL_Quit();
}

void Game::run(){
	while (running) {
		frameStart = SDL_GetTicks();
		userInput.collectInput();
		handleEvents();
		if (userInput.shouldQuit()) {
			running = false;
		}
		renderer.clear();
		renderer.drawRoomTiled(sprites.tileTexture, room.getWidth(), room.getHeight(), room.getTileSize());
		renderer.drawSprite(sprites.playerTexture, player.getX(), player.getY(), 100, 100);
		renderer.present();
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
}
void Game::loadMenu() {};
void Game::enterRoom(int roomId) {};
void Game::killEntity(int entityId) {};

void Game::handleEvents() {
	if (userInput.isWPressed()) {
		player.moveUp();
	}
	if (userInput.isAPressed()) {
		player.moveLeft();
	}
	if (userInput.isSPressed()) {
		player.moveDown();
	}
	if (userInput.isDPressed()) {
		player.moveRight();
	}
}


Sprites& Game::getSprites() { return sprites; }
const Sprites& Game::getSprites() const { return sprites; }
int Game::getFPS() const { return FPS; }
int Game::getFrameDelay() const { return frameDelay; }
Uint32 Game::getFrameStart() const { return frameStart; }
void Game::setFrameStart(Uint32 start) { frameStart = start; }
int Game::getFrameTime() const { return frameTime; }
void Game::setFrameTime(int time) { frameTime = time; }
bool Game::isRunning() const { return running; }
void Game::setRunning(bool status) { running = status; }
Player& Game::getPlayer() { return player; }
const Player& Game::getPlayer() const { return player; }
Renderer& Game::getRenderer() { return renderer; }
const Renderer& Game::getRenderer() const { return renderer; }
UserInput& Game::getUserInput(){return userInput;}
const UserInput& Game::getUserInput() const {	return userInput;}
Room& Game::getRoom() { return room; }
const Room& Game::getRoom() const { return room; }