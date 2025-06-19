#ifndef PLAYER_H
#define PLAYER_H

#include <string>
//#include "Enemy.h"
#include "../Map.h"
#include "../UserInput.h"

class Enemy;

class Player {
private:
    std::string name;
    int health;
    int attackPower;
    int speed;
    int x, y;
    int maxHealth;

    Uint32 lastAttackTime;
    Uint32 attackCooldown;

public:
    struct Animation {
        std::vector<SDL_Texture*> frames;
        int currentFrame = 0;
        int frameTime = 100; // ms
        Uint64 lastUpdate = 0;

        void update() {
            Uint64 now = SDL_GetTicks();
            if (now - lastUpdate >= frameTime) {
                currentFrame = (currentFrame + 1) % frames.size();
                lastUpdate = now;
            }
        }

        SDL_Texture* getCurrentTexture() const {
            return frames[currentFrame];
        }
    };

    bool facingRight;
    Animation walkAnimation;
    Animation idleAnimation;

    Player(const std::string& n, int hp, int atk, int spd, int startX = 0, int startY = 0);
    ~Player();

    void setName(const std::string& name);
    void setHealth(int health);
    void setAttackPower(int attackPower);
    void setSpeed(int speed);
    void setPosition(int posX, int posY);
    void setMaxHealth(int hp);
    int getHealth() const;
    int getAttackPower() const;
    int getSpeed() const;
    int getX() const;
    int getY() const;
    std::string getName() const;
    int getMaxHealth() const;

    void init(const std::string& n, int hp, int atk, int spd, int startX, int startY);
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void moveWithCollision(int dx, int dy, const std::vector<std::vector<int>>& map, int tileSize);
    void tryMoveAxis(int dx, int dy, const std::vector<std::vector<int>>& map, int tileSize, int playerWidth, int playerHeight);
    void takeDamage(int dmg);
    void heal(int amount);
    void attack(Enemy &enemy);
    SDL_FRect getAttackArea();
    void die();
    bool isAlive() const;
    std::string toString() const;
};

#endif
