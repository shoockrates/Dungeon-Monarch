// TODO:

//  Loads assets and sets up entities when entering the room.
// void Room::loadRoom() {}

//  Cleans up objects when leaving the room.
// void Room::unloadRoom() {}


#include "Room.h"

using namespace std;

#define MAX_LEVEL 10

//===================================================

int Room::id = 0;
int Room::objectCount = 0;

//===================================================

Room::Room(int level, bool boss, bool start) {
    this->level = level;
    isCleared = false;
    isBossRoom = boss;
    isStartingRoom = start;
    uniqueID = ++id;
    ++objectCount;
}

Room::~Room() {
    --objectCount;
}

//===================================================

int Room::getLevel() {
    return level;
}
int Room::getUniqueID() {
    return uniqueID;
}
int Room::getObjectCount() {
    return objectCount;
}

//===================================================

void Room::setLevel(int level) {
    if (level < 0) {
        throw invalid_argument("Level cannot be negative number.");
    }
    if (level > MAX_LEVEL) {
        throw invalid_argument("Level cannot exceed " + to_string(MAX_LEVEL) + ".");
    }
    this->level = level;
}


void Room::clearRoom() {
    isCleared = true;
}

//===================================================

string Room::toString() {
    stringstream oss;
    oss << "Room ID: " << uniqueID
        << "; Level: " << level
        << "; Boss Room: " << (isBossRoom ? "Yes" : "No")
        << "; Starting Room: " << (isStartingRoom ? "Yes" : "No")
        << "; Cleared: " << (isCleared ? "Yes" : "No");
    return oss.str();
}
