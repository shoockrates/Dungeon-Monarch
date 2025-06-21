#include "../../include/entities/Enemy.h"
#include "../../include/entities/Player.h"
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <SDL3/SDL.h>
#include "../../include/UI/UIElement.h"

int Enemy::enemyCount = 0;

Enemy::Enemy(const std::string& n, int hp, int atk, int spd, int startX, int startY) {
    init(n, hp, atk, spd, startX, startY);
    enemyCount++;
    lastMoveTime = SDL_GetTicks();
    moveCooldown = 500;
    lastAttackTime = SDL_GetTicks();
    attackCooldown = 1000; // 1 seconds = 1000 ms
    srand(time(0));
}

Enemy::~Enemy() {
    delete healthDisplay;
    enemyCount--;
}

// ! Setters/Getters
    // Setters
void Enemy::setName(const std::string& name) {
    this->name = name;
}

void Enemy::update(Player& player, const std::vector<std::vector<int>>& map, int tileSize) {
    Uint32 currentTime = SDL_GetTicks();

    if(isFollowTrigger(player) && !this->isFollowingPlayer) {
        this->isFollowingPlayer = true;
    }

    if (isPlayerInRange(player)) {
        attack(player);
        
    }
    else if ((currentTime - lastMoveTime > moveCooldown)) {
        //moveRandomly(map, tileSize);
        if(this->isFollowingPlayer){
            followPlayer(player, map, tileSize);
        } else {
            moveRandomly(map, tileSize);
        }
        lastMoveTime = currentTime;
    }
}

bool Enemy::canAttack() const {
    Uint32 currentTime = SDL_GetTicks();
    Uint32 timeSinceLastAttack = currentTime - lastAttackTime;

    if (!initialCooldownPassed) {
        return timeSinceLastAttack >= initialCooldown;
    }
    else {
        return timeSinceLastAttack >= attackCooldown;
    }
}

bool Enemy::isFollowTrigger(Player& player) {
    int dx = player.getX() - x;
    int dy = player.getY() - y;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < 192; // 3 tiles range
}

void Enemy::setFollowingTrigger(bool followTrigger) {
    this->isFollowingPlayer = followTrigger;
}


void Enemy::setHealth(int health) {
    // Ensure health is at least 1
    if (health <= 0) {
        this->health = 1;
        return;
    }
    this->health = health;
}

void Enemy::setAttackPower(int attackPower) {
    // Ensure attack power is at least 1
    if (attackPower <= 0) {
        this->attackPower = 1;
        return;
    }
    this->attackPower = attackPower;
}

void Enemy::setEnemyRect(float x, float y, float w, float h) {
    this->enemyRect.x = x;
    this->enemyRect.y = y;
    this->enemyRect.w = w;
    this->enemyRect.h = h;
}

void Enemy::setHealthDisplay(UIElement* element) {
    this->healthDisplay = element;
}

bool Enemy::isPlayerInRange(const Player& player) const {
    int dx = player.getX() - x;
    int dy = player.getY() - y;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < 96; // 1,5 tile range
}

void Enemy::moveRandomly(const std::vector<std::vector<int>>& map, int tileSize) {
    int direction = rand() % 4;
    int dx = 0, dy = 0;

    switch (direction) {
    case 0: 
        dy += speed;
        break;
    case 1: 
        dy -= speed;
        break;
    case 2: 
        dx -= speed;
        break;
    case 3: 
        dx += speed;
        break;
    }

    moveWithCollision(dx, dy, map, tileSize);
}

void Enemy::followPlayer(const Player& player, const std::vector<std::vector<int>>& map, int tileSize) {
    int dx = (player.getX() > x) ? speed : (player.getX() < x ? -speed : 0);
    int dy = (player.getY() > y) ? speed : (player.getY() < y ? -speed : 0);
    moveWithCollision(dx, dy, map, tileSize);
}

void Enemy::moveWithCollision(int dx, int dy, const std::vector<std::vector<int>>& map, int tileSize) {
    int w = 64;
    int h = 64;

    // horizontal then vertical
    tryMoveAxis(dx, 0, map, tileSize, w, h);
    tryMoveAxis(0, dy, map, tileSize, w, h);
}

void Enemy::tryMoveAxis(int dx, int dy, const std::vector<std::vector<int>>& map, int tileSize, int width, int height) {
    int newX = x + dx;
    int newY = y + dy;

    int leftTile = newX / tileSize;
    int rightTile = (newX + width - 1) / tileSize;
    int topTile = newY / tileSize;
    int bottomTile = (newY + height - 1)/ tileSize;

    if (topTile >= 0 && bottomTile < (int)map.size() &&
        leftTile >= 0 && rightTile < (int)map[0].size())
    {
        bool canMove =
            map[topTile][leftTile]  != 0 &&
            map[topTile][rightTile] != 0 &&
            map[bottomTile][leftTile]  != 0 &&
            map[bottomTile][rightTile] != 0;

        if (canMove) {
            moveX(dx);
            moveY(dy);
            //x = newX;  y = newY;
        }
    }
}

void Enemy::moveX(int dx) {
    x += dx;
    enemyRect.x += dx;
}
void Enemy::moveY(int dy) {
    y += dy;
    enemyRect.y += dy;
}


void Enemy::setSpeed(int speed) {
    // Ensure speed is at least 1
    if (speed <= 0) {
        this->speed = 1;
        return;
    }
    this->speed = speed;
}

void Enemy::setPosition(int posX, int posY) {
    x = posX;
    y = posY;
}

// Getters
int Enemy::getHealth() const {
    return health;
}

int Enemy::getAttackPower() const {
    return attackPower;
}

int Enemy::getSpeed() const {
    return speed;
}

int Enemy::getX() const {
    return x;
}

int Enemy::getY() const {
    return y;
}

std::string Enemy::getName() const {
    return name;
}

UIElement* Enemy::getHealthDisplay() const {
    return healthDisplay;
}

int Enemy::getEnemyCount() {
    return enemyCount;
}
// !

void Enemy::init(const std::string& n, int hp, int atk, int spd, int startX, int startY) {
    setName(n);
    setHealth(hp);
    setAttackPower(atk);
    setSpeed(spd);
    setPosition(startX, startY);
    setEnemyRect(startX, startY, 64, 64);
}

void Enemy::attack(Player& player) {
    if (canAttack()) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastAttackTime > attackCooldown) {
            player.takeDamage(attackPower);
            lastAttackTime = currentTime;
            //std::cout << name << " attacks " << player.getName() << " for " << attackPower << " damage!\n";
        }
    }
}

void Enemy::takeDamage(int dmg) {
    if (dmg < 0) {
        dmg = abs(dmg);
    }
    health -= dmg;
    //std::cout << name << " took " << dmg << " damage. Health: " << health << std::endl;
    if (health <= 0) {
        health = 0;
        die();
    }
}

void Enemy::moveUp() {
    y += speed;
    enemyRect.y += speed;
    //std::cout << name << " moved up to (" << x << ", " << y << ")\n";
}

void Enemy::moveDown() {
    y -= speed;
    enemyRect.y -= speed;
    //std::cout << name << " moved down to (" << x << ", " << y << ")\n";
}

void Enemy::moveRight() {
    x += speed;
    enemyRect.x += speed;
    //std::cout << name << " moved right to (" << x << ", " << y << ")\n";
}

void Enemy::moveLeft() {
    enemyRect.y -= speed;
    x -= speed;
    //std::cout << name << " moved left to (" << x << ", " << y << ")\n";
}

void Enemy::die() {
    //std::cout << name << " has died.\n";
    enemyCount--;
    // TO DO: Maybe add score to player?
}
SDL_FRect Enemy::getEnemyRect() const {
    return enemyRect;
}

bool Enemy::isAlive() const {
    return health > 0;
}

void Enemy::displayHealth(SDL_Renderer* renderer) {
    if (healthDisplay == nullptr) {
        healthDisplay = new UIElement(renderer, x, y, 64, 64);
    }
    healthDisplay->update(x, y, health);
    healthDisplay->render();
}

std::string Enemy::toString() const {
    std::stringstream ss;
    ss << name << " " << health << " " << attackPower << " " << speed << " " << x << " " << y;
    return ss.str();
}
