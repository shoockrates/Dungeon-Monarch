#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include "../UI/UIElement.h"

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
    void setEnemyRect(float x, float y, float w, float h);
    void setHealthDisplay(UIElement* element);

    // Getters
    int getHealth() const;
    int getAttackPower() const;
    int getSpeed() const;
    int getX() const;
    int getY() const;
    std::string getName() const;
    UIElement* getHealthDisplay() const;
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
    SDL_FRect getEnemyRect() const;
    void displayHealth(SDL_Renderer* renderer);
    bool canAttack() const;

    // AI methods
    void update(Player& player, const std::vector<std::vector<int>>& map, int tileSize);

    struct Animation {
        std::vector<SDL_Texture*> frames;
        int currentFrame = 0;
        int frameTime = 100; // ms
        Uint64 lastUpdate = 0;
        bool animationRunning = 0;

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

    // bool facingRight;
    bool wasAttacked;
    Animation hurtAnimation;
    Animation idleAnimation;

private:
    bool isPlayerInRange(const Player& player) const;
    void moveRandomly(const std::vector<std::vector<int>>& map, int tileSize);

    // AI helper methods
    bool isFollowTrigger(Player& player);
    void setFollowingTrigger(bool followTrigger);
    void moveX(int dx);
    void moveY(int dy);
    void followPlayer(const Player& player, const std::vector<std::vector<int>>& map, int tileSize);
    void moveWithCollision(int dx, int dy, const std::vector<std::vector<int>>& map, int tileSize);
    void tryMoveAxis(int dx, int dy, const std::vector<std::vector<int>>& map, int tileSize, int width, int height);

    std::string name;
    int health;
    int attackPower;
    int speed;
    int x;
    int y;
    static int enemyCount;
    SDL_FRect enemyRect;
    UIElement* healthDisplay = nullptr;

    Uint32 lastAttackTime;
    Uint32 attackCooldown;

    Uint32 initialCooldown = 2000; // 2 seconds = 2000ms
    bool initialCooldownPassed = false;

    // AI variables
    Uint32 lastMoveTime;
    Uint32 moveCooldown;
    bool isFollowingPlayer = false;
};

#endif // ENEMY_H
