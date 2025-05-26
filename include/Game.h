#ifndef GAME_H
#define GAME_H

#include "entities/Player.h"
#include "entities/Enemy.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Room.h"
#include "Sprites.h"
#include "menuSystem/StartMenu.h"
#include "menuSystem/PauseMenu.h"
#include "SaveManager.h"

#include "Map.h"
#include <vector>
/*
 * TODO:
 * - Integrate menu system 
 * - Implement room management logic (room transitions, room loading, player positioning).
 * - Implement enemy system (design and integrate missing enemy fields and behavior).
 * - Implement player boundary logic (prevent movement outside visible room bounds).
 * - Implement attack system (add mechanics for player attacks and interaction with enemies).
 * - Improve graphical assets (replace placeholder sprites with higher-quality images).
 */

class Game {
public:
    Game();
    ~Game();

    /**
  * Main loop of the game.
  *
  * Handles user input collection, event processing, game state updates, rendering,
  * and frame rate limiting. Continuously executes while the game is marked as running.
  */
    void run();

    /**
     * Prepares and displays the main menu or other in-game menus.
     *
     * Currently unimplemented. Placeholder for future expansion
     * when menu screens, such as start menu, pause menu, or settings,
     * are integrated into the project.
     */
    void loadMenu();

    /**
     * Handles logic for entering a specific room based on its identifier.
     *
     * Currently unimplemented. Designed for future development where
     * transitioning between rooms will involve loading new assets,
     * setting up entities, and configuring player position.
     */
    void enterRoom(int roomId);

    /**
     * Handles the logic associated with the destruction or removal of an entity.
     *
     * Currently unimplemented. Intended for future use when entities such as
     * enemies, destructible objects, or interactive elements need to be removed
     * from the game world as part of combat or interactions.
     */
    void killEntity(int entityId);

    Sprites& getSprites();
    const Sprites& getSprites() const;
    int getFPS() const;
    int getFrameDelay() const;
    Uint32 getFrameStart() const;
    void setFrameStart(Uint32 start);
    int getFrameTime() const;
    void setFrameTime(int time);
    bool isRunning() const;
    void setRunning(bool status);
    Player& getPlayer();
    const Player& getPlayer() const;
    Renderer& getRenderer();
    const Renderer& getRenderer() const;
    UserInput& getUserInput();
    const UserInput& getUserInput() const;
    std::vector<Enemy>& getEnemies() { return enemies; }
    Room& getRoom();
    const Room& getRoom() const;
private:
    Sprites sprites;

    int mapCounter = 0;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    bool running = true;

    Player player = Player("Placeholder", 100, 10, 5, 64, 64);
    Renderer renderer = Renderer(Room::getWidth(), Room::getHeight(), Room::getTileSize());
    SaveManager saveManager{renderer.getRenderer()};
    StartMenu startMenu{renderer.getRenderer(), &saveManager};
    PauseMenu pauseMenu{renderer.getRenderer(), &saveManager};
    std::vector<Enemy> enemies;
    UserInput userInput;
    Room room = Room(0, false, true);

    void handleEvents();
};

#endif
