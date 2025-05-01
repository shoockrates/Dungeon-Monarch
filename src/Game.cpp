#include "../include/Game.h"

Map map;

Game::Game() {
    map.loadMap("map.txt");
    try {
        sprites.tileTexture = renderer.loadSprite("assets/test.bmp");
        sprites.playerTexture = renderer.loadSprite("assets/knight.bmp");
        sprites.groundTexture = renderer.loadSprite("assets/ground.bmp");
        sprites.enemyTexture = renderer.loadSprite("assets/zombie.bmp");
    }
    catch (const std::exception& e) {
        SDL_Log("Sprite loading failed: %s", e.what());
        running = false;
    }
    enemies.push_back(Enemy("Zombie", 50, 10, 2, 300, 200));
    enemies.push_back(Enemy("Zombie", 50, 10, 2, 500, 400));
}

Game::~Game() {
    SDL_DestroyTexture(sprites.tileTexture);
    SDL_DestroyTexture(sprites.playerTexture);
    SDL_DestroyTexture(sprites.enemyTexture);
    SDL_DestroyTexture(sprites.groundTexture);
    SDL_Quit();
}

void Game::run() {
    while (running) {
        frameStart = SDL_GetTicks();
        userInput.collectInput();
        handleEvents();
        if (userInput.shouldQuit()) {
            running = false;
        }

        // Update enemies
        for (auto& enemy : enemies) {
            if (enemy.isAlive()) {
                enemy.update(player, map.getMap(), 64);
            }
        }

        renderer.clear();
        renderer.drawRoomTiled(sprites.tileTexture, room.getWidth(), room.getHeight(), room.getTileSize());
        map.renderMap(renderer.getSDLRenderer(), sprites.tileTexture, sprites.groundTexture, 64);
        renderer.drawSprite(sprites.playerTexture, player.getX(), player.getY(), 64, 64);

        for (auto& enemy : enemies) {
            if (enemy.isAlive()) {
                renderer.drawSprite(sprites.enemyTexture, enemy.getX(), enemy.getY(), 64, 64);
            }
        }

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
		player.moveWithCollision(0, -(player.getSpeed()), map.getMap(), 64);
		//player.moveUp();
	}
	if (userInput.isAPressed()) {
		player.moveWithCollision(-player.getSpeed(), 0, map.getMap(), 64);
		//player.moveLeft();
	}
	if (userInput.isSPressed()) {
		player.moveWithCollision(0, player.getSpeed(), map.getMap(), 64);
		//player.moveDown();
	}
	if (userInput.isDPressed()) {
		player.moveWithCollision(player.getSpeed(), 0, map.getMap(), 64);
		//player.moveRight();
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
