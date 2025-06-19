#include "../include/Game.h"

Map map;

Game::Game() {
    mapCounter = 1;
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
                enemies.clear(); // Important to reset before loading new map

                if (mapCounter >= 5) {
                    // TODO: Padaryti end screena
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Victory", "You won!", NULL);
                    running = false;
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
                    player.setPosition(64, 64); // reset player position if 
                    player.heal(20);
                    userInput.reset(); // reset userInput to prevent movement bugs after entering a new room
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
    // Attack enemies and if the areas intersect, do damage
    if (userInput.isMouseLeftPressed()) {
        SDL_FRect attackRect = player.getAttackArea();
        for (auto& enemy : enemies) {
            if (intersects(attackRect, enemy.getEnemyRect())) {
                //cout << "Attempting to attack enemy: " << enemy.toString() << endl;
                player.attack(enemy);
                renderer.drawSprite(sprites.meleeAttackTexture, (attackRect.x), (attackRect.y), (attackRect.w), (attackRect.h));
            }
        }
        //cout << "Left mouse was clicked " << player.toString() << endl;
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
