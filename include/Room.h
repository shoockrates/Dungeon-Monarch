#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <exception>
#include <sstream>

using namespace std;

class Room {
private:

    int uniqueID;
    static int id;
    static int objectCount;

    static const int width;
    static const int height;
    static const int tileSize;

    int level;

    bool isCleared;
    bool isBossRoom;
    bool isStartingRoom;

public:
    
    /**
     * @brief Constructs a Room object.
     * 
     * @param level The level of the room (default is 0).
     * @param boss Indicates if this is a boss room (default is false).
     * @param start Indicates if this is the starting room (default is false).
     */
    Room(int level = 0, bool boss = false, bool start = false);

    /**
     * @brief Destroys the Room object and manages cleanup.
     */
    ~Room();

    int getLevel();
    int getUniqueID();
    static int getObjectCount();

    static int getWidth();
    static int getHeight();
    static int getTileSize();
    
    void setLevel(int level);

    /**
     * @brief Marks the room as "cleared" after all enemies are defeated.
     */
    void clearRoom();

    /**
     * @brief Returns a string representation of the room's details.
     * 
     * @return A formatted string containing room information.
     */
    string toString();

};

#endif