#include "../../include/entities/Enemy.h"
#include "../../include/entities/Player.h"
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <SDL3/SDL.h>

int Enemy::enemyCount = 0;

Enemy::Enemy(const std::string& n, int hp, int atk, int spd, int startX, int startY) {
    init(n, hp, atk, spd, startX, startY);
    enemyCount++;
    lastMoveTime = SDL_GetTicks();
    moveCooldown = 500;
    srand(time(0));
}

Enemy::~Enemy() {
    enemyCount--;
}

// ! Setters/Getters
    // Setters
void Enemy::setName(const std::string& name) {
    this->name = name;
}

void Enemy::update(Player& player, const std::vector<std::vector<int>>& map, int tileSize) {
    Uint32 currentTime = SDL_GetTicks();

    if (isPlayerInRange(player)) {
        attack(player);
    }
    else if (currentTime - lastMoveTime > moveCooldown) {
        moveRandomly(map, tileSize);
        lastMoveTime = currentTime;
    }
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

bool Enemy::isPlayerInRange(const Player& player) const {
    int dx = player.getX() - x;
    int dy = player.getY() - y;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < 128; // 2 tiles range
}

void Enemy::moveRandomly(const std::vector<std::vector<int>>& map, int tileSize) {
    int direction = rand() % 4;
    int originalX = x;
    int originalY = y;

    switch (direction) {
    case 0: moveUp(); break;
    case 1: moveDown(); break;
    case 2: moveLeft(); break;
    case 3: moveRight(); break;
    }

    int tileX = x / tileSize;
    int tileY = y / tileSize;

    if (tileX < 0 || tileY < 0 ||
        tileY >= (int)map.size() ||
        tileX >= (int)map[0].size() ||
        map[tileY][tileX] != 1) {
        x = originalX;
        y = originalY;
    }
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
    //std::cout << name << " attacks " << player.getName() << " for " << attackPower << " damage!\n";
    player.takeDamage(attackPower);
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

std::string Enemy::toString() const {
    std::stringstream ss;
    ss << name << " " << health << " " << attackPower << " " << speed << " " << x << " " << y;
    return ss.str();
}
