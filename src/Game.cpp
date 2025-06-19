#include "../include/Game.h"
#include <fstream>
#include <sstream>
#include <cstdlib> // For system()

Map map;

Game::Game() {
    mapCounter = 1;
    // Initial save when the game starts
    saveGameState(mapCounter);
    
    map.loadMap("map1.txt", enemies, 64);
    try {
        sprites.tileTexture = renderer.loadSprite("assets/test.bmp");
        sprites.playerTexture = renderer.loadSprite("assets/knight.bmp");
        sprites.groundTexture = renderer.loadSprite("assets/ground.bmp");
        sprites.doorTexture = renderer.loadSprite("assets/door.bmp");
        sprites.enemyTexture = renderer.loadSprite("assets/zombie.bmp");
        sprites.playerTexture = renderer.loadSprite("assets/attack.bmp");
    }
    catch (const std::exception& e) {
        SDL_Log("Sprite loading failed: %s", e.what());
        running = false;
    }
    for(int i = 1; i < 12; ++i) {
        std::string path = "assets/player/walk/walk-with-weapon-" + std::to_string(i) + ".png";
        SDL_Texture* tex = renderer.loadSpritePNG(path);
        player.walkAnimation.frames.push_back(tex);
    }
    for(int i = 1; i < 7; ++i) {
        std::string path = "assets/player/idle/idle-with-weapon-" + std::to_string(i) + ".png";
        SDL_Texture* tex = renderer.loadSpritePNG(path);
        player.idleAnimation.frames.push_back(tex);
    }
}

Game::~Game() {
    SDL_DestroyTexture(sprites.tileTexture);
    SDL_DestroyTexture(sprites.playerTexture);
    SDL_DestroyTexture(sprites.enemyTexture);
    SDL_DestroyTexture(sprites.groundTexture);
    SDL_DestroyTexture(sprites.doorTexture);
    SDL_DestroyTexture(sprites.meleeAttackTexture);

    for (auto* tex : player.walkAnimation.frames) {
        SDL_DestroyTexture(tex);
    }
    SDL_Quit();
}

void Game::saveGameState(int level) {
    std::ofstream stateFile("state.txt");
    if (stateFile.is_open()) {
        stateFile << level;
        stateFile.close();
        std::cout << "Game state saved. Current level: " << level << std::endl;
    } else {
        std::cerr << "Error: Unable to open state.txt for writing." << std::endl;
    }
}

void Game::updateLevelInDB(int level, const std::string& playerName) {
    std::stringstream command;
    // This command calls the Python script to send data.
    // "1" is the command for SEND, followed by the level and player name.
    command << "python SendData.py 1 " << level << " \"" << playerName << "\"";

    std::cout << "Executing command: " << command.str() << std::endl;
    int result = system(command.str().c_str());

    if (result == 0) {
        std::cout << "Successfully updated level in MongoDB." << std::endl;
    } else {
        std::cerr << "Error: Failed to execute Python script or script returned an error." << std::endl;
    }
}

void Game::run(){

	if (!startMenu.run()) {
		running = false;
	}

	while (running) {
		frameStart = SDL_GetTicks();
		userInput.collectInput();
        renderer.clear();
		handleEvents();
		if (userInput.shouldQuit()) {
			running = false;
		}
		if (userInput.isEscPressed()) {
			if (!pauseMenu.run()) {
				running = false;
			}
			userInput.setEscPressed(false);
		}

        // Update enemies
        for (auto& enemy : enemies) {
            if (enemy.isAlive()) {
                enemy.update(player, map.getMap(), 64);
            }
        }

        renderer.drawRoomTiled(sprites.tileTexture, room.getWidth(), room.getHeight(), room.getTileSize());
        map.renderMap(renderer.getSDLRenderer(), sprites.tileTexture, sprites.groundTexture, sprites.doorTexture, 64);

        // if player moves update animation
        if (userInput.isDPressed() || userInput.isAPressed()) {
            player.walkAnimation.update();
        }

        if (userInput.isDPressed()) {
            player.facingRight = true;
            renderer.drawSprite(player.walkAnimation.getCurrentTexture(), player.getX(), player.getY(), 64, 64);
        } else if (userInput.isAPressed()) {
            player.facingRight = false;
            renderer.drawSprite(player.walkAnimation.getCurrentTexture(), player.getX(), player.getY(), 64, 64, true);
        } else {
            renderer.drawSprite(player.idleAnimation.getCurrentTexture(), player.getX(), player.getY(), 64, 64, !player.facingRight);
        }
        

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
        // Clean up dead enemies
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](const Enemy& e) { return !e.isAlive(); }), enemies.end());


        // Check for door entry only if no enemies left
        if (enemies.empty()) {
            int playerTileX = player.getX() / 64;
            int playerTileY = player.getY() / 64;
            int doorTileX = map.doorX / 64;
            int doorTileY = map.doorY / 64;

            if (abs(playerTileX - doorTileX) < 2 && abs(playerTileY - doorTileY) < 2) {
                // Player is close enough to the door to enter the next map
                mapCounter++;
                
                // --- NEW FUNCTIONALITY ---
                // Save the new level to state.txt and send the change to MongoDB
                saveGameState(mapCounter);
                updateLevelInDB(mapCounter, player.getName());
                // --- END NEW FUNCTIONALITY ---

                enemies.clear(); // Important to reset before loading new map

                if (mapCounter >= 5) {
                    // TODO: Padaryti end screena
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Victory", "You won!", NULL);
                    running = false;
                    return;
                } else {
                    std::cout << "Entering next map: " << mapCounter << std::endl;
                    // Load the next map
                    std::string nextMap = "map" + std::to_string(mapCounter) + ".txt";
                    map.loadMap(nextMap, enemies, 64);
                    player.setPosition(64, 64); // reset player position if needed
                }
            }
        }
    }
}
void Game::loadMenu() {};
void Game::enterRoom(int roomId) {};
void Game::killEntity(int entityId) {};

void Game::handleEvents() {
	if (userInput.isWPressed()) {
		player.moveWithCollision(0, -(player.getSpeed()), map.getMap(), 64);
	}
	if (userInput.isAPressed()) {
		player.moveWithCollision(-player.getSpeed(), 0, map.getMap(), 64);
	}
	if (userInput.isSPressed()) {
		player.moveWithCollision(0, player.getSpeed(), map.getMap(), 64);
	}
	if (userInput.isDPressed()) {
		player.moveWithCollision(player.getSpeed(), 0, map.getMap(), 64);
	}
    if (userInput.isMouseLeftPressed()) {
        SDL_FRect attackRect = player.getAttackArea();
        for (auto& enemy : enemies) {
            if (intersects(attackRect, enemy.getEnemyRect())) {
                player.attack(enemy);
                renderer.drawSprite(sprites.meleeAttackTexture, (attackRect.x), (attackRect.y), (attackRect.w), (attackRect.h));
            }
        }
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
