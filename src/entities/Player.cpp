#include "../../include/entities/Player.h"
#include "../../include/entities/Enemy.h"
#include "../../include/UserInput.h"
#include "../../include/Direction.h"
#include <iostream>
#include <sstream>

#define MAX_HEALTH 100

Player::Player(const std::string& n, int hp, int atk, int spd, int startX, int startY, direction facing){
    init(n, hp, atk, spd, startX, startY, facing);
}

Player::~Player() {
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

    void Player::setFacing(direction facing) {
        this->facing = facing;
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
    
    direction Player::getFacing() const {
        return facing;
    }

    std::string Player::getName() const {
        return name;
    }
// !

void Player::init(const std::string& n, int hp, int atk, int spd, int startX, int startY,direction facing) {
    setName(n);
    setHealth(hp);
    setAttackPower(atk);
    setSpeed(spd);
    setPosition(startX, startY);
    setFacing(facing);
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
    int rightTile  = (newX + playerWidth  - 1) / tileSize;
    int topTile    = newY / tileSize;
    int bottomTile = (newY + playerHeight - 1) / tileSize;

    if (topTile >= 0 && bottomTile < (int)map.size() &&
        leftTile >= 0 && rightTile < (int)map[0].size())
    {
        // only if all four corners are free
        bool canMove = (map[topTile][leftTile]   == 1) &&
                       (map[topTile][rightTile]  == 1) &&
                       (map[bottomTile][leftTile]== 1) &&
                       (map[bottomTile][rightTile]==1);

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
    if(health + amount > MAX_HEALTH){
        health = MAX_HEALTH;
        return;
    }
    health += amount;
    //std::cout << name << " healed " << amount << ". Health: " << health << std::endl;
}

void Player::attack(Enemy& enemy) {
    //std::cout << name << " attacks " << enemy.getName() << " for " << attackPower << " damage!\n";
    enemy.takeDamage(attackPower);
}

void Player::die() {
    //std::cout << name << " has died.\n";
    //TO DO: Show end screen
}

bool Player::isAlive() const {
    return health > 0;
}

//If the player is moving on both vertical and horizontal axis, the horizontal axis will be prioritized
void Player::isFacing(UserInput input){
    bool up = input.isWPressed();
    bool down = input.isSPressed();
    bool left = input.isAPressed();
    bool right = input.isDPressed();
    
    bool vertical = up ^ down;
    bool horizontal = right ^ left;

    if (horizontal && !vertical) { 
        facing = right ? RIGHT : LEFT;
    }
    else if (!horizontal && vertical) {
        facing = up ? UP : DOWN;
    }
    else if (horizontal && vertical) {
        facing = right ? RIGHT : LEFT;
    }
}

SDL_FRect Player::getAttackArea() {
    SDL_FRect attackArea;


    switch (facing) {
    case UP:
        attackArea.x = x;
        attackArea.y = y - 64;
        break;
    case DOWN:
        attackArea.x = x;
        attackArea.y = y + 64;
        break;
    case LEFT:
        attackArea.x = x - 64;
        attackArea.y = y;
        break;
    case RIGHT:
        attackArea.x = x + 64;
        attackArea.y = y;
        break;
    }

    return attackArea;
}
const char* Player::directionToString(direction d) const{
    switch (d) {
    case UP:    return "UP";
    case DOWN:  return "DOWN";
    case LEFT:  return "LEFT";
    case RIGHT: return "RIGHT";
    default:    return "UNKNOWN";
    }
}

std::string Player::toString() const{
    std::stringstream ss;
    ss << name << " " << health << " " <<  attackPower << " " << speed << " " << x << " " << y << " " << directionToString(facing);
    return ss.str();
}
