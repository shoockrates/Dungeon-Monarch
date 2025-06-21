#include "../include/Game.h"

#include <fstream>
#include <sstream>
#include <cstdlib> // For system()

#include "../include/UI/UIElement.h"


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
        //sprites.enemyTexture = renderer.loadSprite("assets/zombie.bmp");
        sprites.playerTexture = renderer.loadSprite("assets/attack.bmp");
    
        player.attackAnimation.currentFrame = -1;

        for(int i = 0; i <= 7; ++i) {
            std::string path = "assets/player/walk/walk-" + std::to_string(i) + ".png";
            SDL_Texture* tex = renderer.loadSpritePNG(path);
            player.walkAnimation.frames.push_back(tex);
        }
        
        for(int i = 0; i <= 5; ++i) {
            std::string path = "assets/player/attack/attack-" + std::to_string(i) + ".png";
            SDL_Texture* tex = renderer.loadSpritePNG(path);
            player.attackAnimation.frames.push_back(tex);
        }

        for(int i = 0; i <= 5; ++i) {
            std::string path = "assets/player/idle/idle-" + std::to_string(i) + ".png";
            SDL_Texture* tex = renderer.loadSpritePNG(path);
            player.idleAnimation.frames.push_back(tex);
        }

        loadEnemies();

    }
    catch (const std::exception& e) {
        SDL_Log("Sprite loading failed: %s", e.what());
        running = false;
    }



    //enemies.push_back(Enemy("Zombie", 50, 10, 2, 300, 200));
    //enemies.push_back(Enemy("Zombie", 50, 10, 2, 500, 400));

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


		
		//renderer.drawSprite(sprites.playerTexture, player.getX(), player.getY(), 100, 100);
		/*renderer.drawSprite(sprites.groundTexture, 0, 0, 30, 30);
		renderer.drawSprite(sprites.groundTexture, 100, 0, 30, 30);
		renderer.drawSprite(sprites.groundTexture, 0, 100, 30, 30);
		renderer.drawSprite(sprites.groundTexture, 100, 100, 30, 30);*/

        // check if player died
        if(player.getHealth() <= 0) {
            if (!loseMenu.run()) {
                running = false;
            }
        }


        // Update enemies
        for (auto& enemy : enemies) {
            if (enemy.isAlive()) {
                enemy.update(player, map.getMap(), 64);
                
            }
        }

        renderer.drawRoomTiled(sprites.tileTexture, room.getWidth(), room.getHeight(), room.getTileSize());
        map.renderMap(renderer.getSDLRenderer(), sprites.tileTexture, sprites.groundTexture, sprites.doorTexture, 64);

        // Animation update
        if (player.attackAnimation.currentFrame >= 0) {
            if (player.attackAnimation.currentFrame >= 5) {
                player.attackAnimation.currentFrame = -1;
                player.attackAnimation.animationRunning = 0;
            } else {
                player.attackAnimation.update();
            }
        } else if (userInput.isDPressed() || userInput.isAPressed()) {
            player.walkAnimation.update();
        } else {
            player.idleAnimation.update();
        }

        if (userInput.isDPressed()) {
            player.facingRight = true;
        } else if (userInput.isAPressed()) {
            player.facingRight = false;
        }
        // Animation
        if (player.attackAnimation.currentFrame >= 0 && player.attackAnimation.currentFrame <= 5) {
            renderer.drawSprite(player.attackAnimation.getCurrentTexture(), player.getX(), player.getY(), 68, 54, !player.facingRight);
        } if (userInput.isDPressed() || userInput.isAPressed()) {
            renderer.drawSprite(player.walkAnimation.getCurrentTexture(), player.getX(), player.getY(), 68, 54, !player.facingRight);
        } else {
            renderer.drawSprite(player.idleAnimation.getCurrentTexture(), player.getX(), player.getY(), 68, 54, !player.facingRight);
        }

        // Enemy animation
        for (auto& enemy : enemies) {
            if (enemy.wasAttacked && enemy.hurtAnimation.currentFrame >= 3) {
                enemy.hurtAnimation.currentFrame = -1;
                enemy.wasAttacked = 0;
            } else if (enemy.wasAttacked && enemy.hurtAnimation.currentFrame <= 3) {
                enemy.hurtAnimation.update();
                renderer.drawSprite(enemy.hurtAnimation.getCurrentTexture(), enemy.getX(), enemy.getY(), 46, 30, true);
            } else {
                enemy.idleAnimation.update();
                renderer.drawSprite(enemy.idleAnimation.getCurrentTexture(), enemy.getX(), enemy.getY(), 46, 30, true);
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

                enemies.clear(); // Important to reset before loading new map
               

                if (mapCounter >= 5) {
                    if (!winMenu.run()) {
                        running = false;
                    }
                    return;
                } else {
                    int upgradeCode = upgradeMenu.run();
                    if (upgradeCode == 2) {
                        //std::cout << "Upgrading attack " << player.getAttackPower();
                        player.setAttackPower(player.getAttackPower() + 1);
                        //std::cout << " -> " << player.getAttackPower() << std::endl;
                    } else if(upgradeCode == 3) {
                        //std::cout << "Upgrading max health " << player.getMaxHealth();
                        player.setMaxHealth(player.getMaxHealth() + 10);
                        //std::cout << " -> " << player.getMaxHealth() << std::endl;
                    }


                    std::cout << "Entering next map: " << mapCounter << std::endl;
                    // Load the next map
                    std::string nextMap = "map" + std::to_string(mapCounter) + ".txt";
                    map.loadMap(nextMap, enemies, 64);
                    loadEnemies();

                    player.setPosition(64, 64); // reset player position if 
                    player.heal(20);
                    userInput.reset(); // reset userInput to prevent movement bugs after entering a new room
                }
            }
        }
        player.displayHealth(renderer.getRenderer());


        // This should be at the end of this method as this takes care of FPS cap
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

void Game::loadEnemies() {
    for (auto& enemy : enemies) {
        enemy.hurtAnimation.currentFrame = -1;
        enemy.wasAttacked = 0;
        for(int i = 0; i <= 3; ++i) {
            std::string path = "assets/enemy/hurt/hurt-" + std::to_string(i) + ".png";
            SDL_Texture* tex = renderer.loadSpritePNG(path);
            enemy.hurtAnimation.frames.push_back(tex);
        }
        SDL_Texture* tex = renderer.loadSpritePNG("assets/enemy/idle/idle.png");
        enemy.idleAnimation.frames.push_back(tex);
    }
}

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

    // Attack enemies and if the areas intersect, do damage
    if (userInput.isMouseLeftPressed() && !player.attackAnimation.animationRunning) {
        player.attackAnimation.currentFrame = 0; // set for animation
        player.attackAnimation.animationRunning = 1;

        SDL_FRect attackRect = player.getAttackArea();
        for (auto& enemy : enemies) {
            if (intersects(attackRect, enemy.getEnemyRect())) {
                player.attack(enemy);
                enemy.wasAttacked = true;
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
