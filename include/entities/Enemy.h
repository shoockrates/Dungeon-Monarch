#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>
#include <SDL3/SDL.h>

class Player;

class Enemy {
public:
    Enemy(const std::string& n, int hp, int atk, int spd, int startX, int startY);
    ~Enemy();

    // Setters
    void setName(const std::string& name);
    void setHealth(int health);
    void setAttackPower(int attackPower);
    void setSpeed(int speed);
    void setPosition(int posX, int posY);
    void setEnemyRect(SDL_FRect rect);

    // Getters
    int getHealth() const;
    int getAttackPower() const;
    int getSpeed() const;
    int getX() const;
    int getY() const;
    std::string getName() const;
    SDL_FRect getEnemyRect() const;
  
    static int getEnemyCount();

    void init(const std::string& n, int hp, int atk, int spd, int startX, int startY);
    void attack(Player& player);
    void takeDamage(int dmg);
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void die();
    bool isAlive() const;
    std::string toString() const;

    // AI methods
    void update(Player& player, const std::vector<std::vector<int>>& map, int tileSize);

private:
    bool isPlayerInRange(const Player& player) const;
    void moveRandomly(const std::vector<std::vector<int>>& map, int tileSize);

    std::string name;
    int health;
    int attackPower;
    int speed;
    int x;
    int y;
    static int enemyCount;

    // AI variables
    Uint32 lastMoveTime;
    Uint32 moveCooldown;

    SDL_FRect enemyRect;
};

#endif // ENEMY_H
