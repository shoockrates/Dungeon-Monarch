#ifndef PLAYER_H
#define PLAYER_H

#include <string>
//#include "Enemy.h"
#include "../Map.h"
#include "../Direction.h"
#include "../UserInput.h"

class Enemy;

class Player {
private:
    std::string name;
    int health;
    int attackPower;
    int speed;
    int x, y;
    direction facing;

public:
    Player(const std::string& n, int hp, int atk, int spd, int startX = 0, int startY = 0, direction facing = RIGHT);
    ~Player();

    void setName(const std::string& name);
    void setHealth(int health);
    void setAttackPower(int attackPower);
    void setSpeed(int speed);
    void setPosition(int posX, int posY);
    void setFacing(direction facing);
    int getHealth() const;
    int getAttackPower() const;
    int getSpeed() const;
    int getX() const;
    int getY() const;
    direction getFacing() const;
    std::string getName() const;

    void init(const std::string& n, int hp, int atk, int spd, int startX, int startY, direction facing);
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void moveWithCollision(int dx, int dy, const std::vector<std::vector<int>>& map, int tileSize);
    void tryMoveAxis(int dx, int dy, const std::vector<std::vector<int>>& map, int tileSize, int playerWidth, int playerHeight);
    void takeDamage(int dmg);
    void heal(int amount);
    void attack(Enemy &enemy);
    void die();
    bool isAlive() const;
    void isFacing(UserInput input);
    SDL_FRect getAttackArea();
    const char* directionToString(direction d) const;
    std::string toString() const;
};

#endif
