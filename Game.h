#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Enemy.h"
#include "Room.h"

class Game {
public:
    Game();
    ~Game();

    void run();
    void loadMenu();
    void enterRoom(int roomId);
    void killEntity(int entityId);

    bool getRunning() const;
    UserInput getUserInput() const;

private:
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    bool running = true;

    Player player = Player("Placeholder", 100, 10, 10, 0, 0);
    Renderer renderer = Renderer(Room::getWidth(), Room::getHeight(), Room::getTileSize());
    UserInput userInput;
    Room room = Room(0, false, true);

    SDL_Texture* testSprite = nullptr;
    void handleEvents();
};

#endif
