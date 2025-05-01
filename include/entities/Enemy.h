#ifndef ENEMY_H
#define ENEMY_H

#include <string>
//#include "Player.h"

class Player;

class Enemy {
private:
    std::string name;
    int health;
    int attackPower;
    int speed;
    int x, y;
    static int enemyCount;

public:
    Enemy(const std::string& n, int hp, int atk, int spd, int startX = 0, int startY = 0);
    ~Enemy();

    void setName(const std::string& name);
    void setHealth(int health);
    void setAttackPower(int attackPower);
    void setSpeed(int speed);
    void setPosition(int posX, int posY);
    int getHealth() const;
    int getAttackPower() const;
    int getSpeed() const;
    int getX() const;
    int getY() const;
    std::string getName() const;
    static int getEnemyCount();

    void init(const std::string& n, int hp, int atk, int spd, int startX, int startY);
    void attack(Player &player);
    void takeDamage(int dmg);
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void die();
    bool isAlive() const;
    std::string toString() const;
};

#endif
