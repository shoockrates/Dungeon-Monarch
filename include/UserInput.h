#ifndef USERINPUT_H
#define USERINPUT_H

#include <SDL3/SDL.h>
#include <string>
#include <sstream>

/**
 * Handles SDL input events for keyboard and mouse.
 * Tracks WASD keys, left mouse button, and cursor position.
 */

class UserInput {
private:
    bool quitRequested = false;
    bool wPressed = false;
    bool aPressed = false;
    bool sPressed = false;
    bool dPressed = false;
    bool escPressed = false;
    bool mouseLeftPressed = false;
    int mouseX = 0;
    int mouseY = 0;
    static int objectCount;

public:
    /**
     * Constructor increments input object counter.
     */
    UserInput();

    /**
     * Destructor decrements input object counter.
     */
    ~UserInput();

    /**
     * Polls SDL events and updates input state.
     */
    void collectInput();

    /**
    * Checks if mouse is over a certain coordinate and checks if it's in the right place
    */
    bool isMouseOver(SDL_FRect rect, int x, int y);

    /**
    * Resets user input. Good idea to call it after entering a new room.
    */
    void reset();

    bool isWPressed() const;
    bool isAPressed() const;
    bool isSPressed() const;
    bool isDPressed() const;
    bool isMouseLeftPressed() const;
    int getMouseX() const;
    int getMouseY() const;
    bool shouldQuit() const;
    bool isEscPressed() const;

    void setWPressed(bool state);
    void setAPressed(bool state);
    void setSPressed(bool state);
    void setDPressed(bool state);
    void setMouseLeftPressed(bool state);
    void setMousePosition(int x, int y);
    void setEscPressed(bool state);

    /**
    * Returns a string summary of input state.
    */
    std::string toString() const;
};

#endif