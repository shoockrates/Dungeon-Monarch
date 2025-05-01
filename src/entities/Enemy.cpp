#include "../../include/entities/Enemy.h"
#include "../../include/entities/Player.h"
#include <iostream>
#include <string>
#include <sstream>

int Enemy::enemyCount = 0; // Static member variable for tracking enemy count

Enemy::Enemy(const std::string& n, int hp, int atk, int spd, int startX, int startY) {
    init(n, hp, atk, spd, startX, startY);
    enemyCount++;
    //std::cout << "Enemy created: " << name << ". Total enemies: " << enemyCount << std::endl;
}

Enemy::~Enemy() {
    //std::cout << "Enemy destroyed: " << name << ". Remaining enemies: " << enemyCount << std::endl;
}

// ! Setters/Getters
    // Setters
    void Enemy::setName(const std::string& name) {
        this->name = name;
    }

    void Enemy::setHealth(int health) {
        // Ensure health is at least 1
        if(health <= 0){
            this->health = 1;
            return;
        }
        this->health = health;
    }

    void Enemy::setAttackPower(int attackPower) {
        // Ensure attack power is at least 1
        if(attackPower <= 0){
            this->attackPower = 1;
            return;
        }
        this->attackPower = attackPower;
    }

    void Enemy::setSpeed(int speed) {
        // Ensure speed is at least 1
        if(speed <= 0){
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
}

void Enemy::attack(Player &player) {
    //std::cout << name << " attacks " << player.getName() << " for " << attackPower << " damage!\n";
    player.takeDamage(attackPower);
}

void Enemy::takeDamage(int dmg) {
    if(dmg < 0){
        dmg = abs(dmg);
    }
    health -= dmg;
    //std::cout << name << " took " << dmg << " damage. Health: " << health << std::endl;
    if (health <= 0){
        health = 0;
        die();
    }
}

void Enemy::moveUp() {
    y += speed;
    //std::cout << name << " moved up to (" << x << ", " << y << ")\n";
}

void Enemy::moveDown() {
    y -= speed;
    //std::cout << name << " moved down to (" << x << ", " << y << ")\n";
}

void Enemy::moveRight() {
    x += speed;
    //std::cout << name << " moved right to (" << x << ", " << y << ")\n";
}

void Enemy::moveLeft() {
    x -= speed;
    //std::cout << name << " moved left to (" << x << ", " << y << ")\n";
}

void Enemy::die() {
    //std::cout << name << " has died.\n";
    enemyCount--;
    // TO DO: Maybe add score to player?
}

bool Enemy::isAlive() const {
    return health > 0;
}

std::string Enemy::toString() const {
    std::stringstream ss;
    ss << name << " " << health << " " <<  attackPower << " " << speed << " " << x << " " << y;
    return ss.str();
}