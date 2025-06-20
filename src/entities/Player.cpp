#include "../../include/entities/Player.h"
#include "../../include/entities/Enemy.h"
#include <iostream>
#include <sstream>

Player::Player(const std::string& n, int hp, int atk, int spd, int startX, int startY){
    init(n, hp, atk, spd, startX, startY);
    lastAttackTime = SDL_GetTicks();
    attackCooldown = 800; // 0.8 seconds = 800 ms
}

Player::~Player() {
    delete healthDisplay;
    //std::cout << "Player destroyed: " << name << std::endl;
}

// ! Setters/Getters
    // Setters
    void Player::setName(const std::string& name) {
        this->name = name;
    }

    void Player::setHealth(int health) {
        // Ensure health is at least 1
        if(health <= 0){
            this->health = 1;
            return;
        }
        this->health = health;
    }

    void Player::setAttackPower(int attackPower) {
        // Ensure attack power is at least 1
        if(attackPower <= 0){
            this->attackPower = 1;
            return;
        }
        this->attackPower = attackPower;
    }

    void Player::setSpeed(int speed) {
        // Ensure speed is at least 1
        if(speed <= 0){
            this->speed = 1;
            return;
        }
        this->speed = speed;
    }

    void Player::setPosition(int posX, int posY) {
        x = posX;
        y = posY;
    }

    void Player::setMaxHealth(int hp) {
        if (hp >= 0) {
            maxHealth = hp;
        }
    }
    
    void Player::setHealthDisplay(UIElement* element) {
        this->healthDisplay = element;
    }

    // Getters
    int Player::getHealth() const {
        return health;
    }

    int Player::getAttackPower() const {
        return attackPower;
    }

    int Player::getSpeed() const {
        return speed;
    }

    int Player::getX() const {
        return x;
    }

    int Player::getY() const {
        return y;
    }

    std::string Player::getName() const {
        return name;
    }

    int Player::getMaxHealth() const {
        return maxHealth;
    }

    UIElement* Player::getHealthDisplay() const {
        return healthDisplay;
    }
// !

void Player::init(const std::string& n, int hp, int atk, int spd, int startX, int startY) {
    setName(n);
    setHealth(hp);
    setAttackPower(atk);
    setSpeed(spd);
    setPosition(startX, startY);
    setMaxHealth(hp);
}

void Player::moveUp() {
    y -= speed;
    //std::cout << name << " moved up to (" << x << ", " << y << ")\n";
}

void Player::moveDown() {
    y += speed;
    //std::cout << name << " moved down to (" << x << ", " << y << ")\n";
}

void Player::moveRight() {
    x += speed;
    //std::cout << name << " moved right to (" << x << ", " << y << ")\n";
}

void Player::moveLeft() {
    x -= speed;
    //std::cout << name << " moved left to (" << x << ", " << y << ")\n";
}

void Player::moveWithCollision(int dx, int dy, const std::vector<std::vector<int>>& map, int tileSize) {
    int playerWidth  = tileSize;
    int playerHeight = tileSize;

    // first try horizontal
    tryMoveAxis(dx, 0, map, tileSize, playerWidth, playerHeight);
    // then vertical
    tryMoveAxis(0, dy, map, tileSize, playerWidth, playerHeight);
}

void Player::tryMoveAxis(int dx, int dy, const std::vector<std::vector<int>>& map, int tileSize, int playerWidth, int playerHeight) {
    int newX = x + dx, newY = y + dy;
    int leftTile   = newX / tileSize;
    int rightTile  = (newX + playerWidth  - 10) / tileSize;
    int topTile    = newY / tileSize;
    int bottomTile = (newY + playerHeight - 10) / tileSize;

    if (topTile >= 0 && bottomTile < (int)map.size() &&
        leftTile >= 0 && rightTile < (int)map[0].size())
    {
        // only if all four corners are free
        bool canMove =
        (map[topTile][leftTile] != 0) &&
        (map[topTile][rightTile] != 0) &&
        (map[bottomTile][leftTile] != 0) &&
        (map[bottomTile][rightTile] != 0);
          
        //std::cout << "Player can move: " << canMove << " " << map[topTile][leftTile] << " " << map[topTile][rightTile] << " " << map[bottomTile][leftTile] << " " << map[bottomTile][rightTile] << std::endl;

        if (canMove) {
            x = newX;  y = newY;
        }
    }
}

void Player::takeDamage(int dmg) {
    health -= dmg;
    //std::cout << name << " took " << dmg << " damage. Health: " << health << std::endl;
    if (health <= 0) die();
}

void Player::heal(int amount) {
    if(health + amount > maxHealth){
        health = maxHealth;
        return;
    }
    health += amount;
    //std::cout << name << " healed " << amount << ". Health: " << health << std::endl;
}

void Player::attack(Enemy &enemy) {
    //std::cout << name << " attacks " << enemy.getName() << " for " << attackPower << " damage!\n";
    Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastAttackTime > attackCooldown) {
            enemy.takeDamage(attackPower);
            lastAttackTime = currentTime;
        }
}

void Player::die() {
    //std::cout << name << " has died.\n";
    //TO DO: Show end screen
}

bool Player::isAlive() const {
    return health > 0;
}
SDL_FRect Player::getAttackArea() {
    SDL_FRect attackArea;

    switch(facingRight){
    case true:
        attackArea.x = x;
        attackArea.y = y;
        break;
    case false:
        attackArea.x = x - 64;
        attackArea.y = y;
        break;
    }
    attackArea.h = 64;
    attackArea.w = 64;

    return attackArea;
}

void Player::displayHealth(SDL_Renderer* renderer) {
    if (healthDisplay == nullptr) {
        healthDisplay = new UIElement(renderer, x, y, 64, 64);
    }
    healthDisplay->update(x, y, health);
    healthDisplay->render();
}

std::string Player::toString() const {
    std::stringstream ss;
    ss << name << " " << health << " " <<  attackPower << " " << speed << " " << x << " " << y << " " << facingRight;
    return ss.str();
}
