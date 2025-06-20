#include "../include/UserInput.h"

int UserInput::objectCount = 0;

UserInput::UserInput() {
    objectCount++;
}

UserInput::~UserInput() {
    objectCount--;
}

bool UserInput::isMouseOver(SDL_FRect rect, int x, int y) {
    return (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h);
}

void UserInput::collectInput() {
    quitRequested = false;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            quitRequested = true;
            break;
        case SDL_EVENT_KEY_DOWN:
            //SDL_Log("Key pressed: %s", SDL_GetKeyName(event.key.key));
            switch (event.key.key) {
            case SDLK_ESCAPE: escPressed = true; break;
            case SDLK_W: wPressed = true; break;
            case SDLK_A: aPressed = true; break;
            case SDLK_S: sPressed = true; break;
            case SDLK_D: dPressed = true; break;
            default: break;
            }
            break;
        case SDL_EVENT_KEY_UP:
            //SDL_Log("Key released: %s", SDL_GetKeyName(event.key.key));
            switch (event.key.key) {
            case SDLK_ESCAPE: escPressed = false; break;
            case SDLK_W: wPressed = false; break;
            case SDLK_A: aPressed = false; break;
            case SDLK_S: sPressed = false; break;
            case SDLK_D: dPressed = false; break;
            default: break;
            }
            break;
        case SDL_EVENT_MOUSE_MOTION:
            mouseX = static_cast<int>(event.motion.x);
            mouseY = static_cast<int>(event.motion.y);
            //SDL_Log("Mouse moved to (%d, %d)", mouseX, mouseY);
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseLeftPressed = true;
                //SDL_Log("Left mouse button pressed at (%d, %d)", mouseX, mouseY);
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseLeftPressed = false;
                //SDL_Log("Left mouse button released at (%d, %d)", mouseX, mouseY);
            }
            break;
        default:
            break;
        }
    }
}
void UserInput::reset() {
    setWPressed(0);
    setAPressed(0);
    setDPressed(0);
    setSPressed(0);
    setMouseLeftPressed(0);
}

bool UserInput::isWPressed() const { return wPressed; }
bool UserInput::isAPressed() const { return aPressed; }
bool UserInput::isSPressed() const { return sPressed; }
bool UserInput::isDPressed() const { return dPressed; }
bool UserInput::isMouseLeftPressed() const { return mouseLeftPressed; }
int UserInput::getMouseX() const { return mouseX; }
int UserInput::getMouseY() const { return mouseY; }
bool UserInput::shouldQuit() const { return quitRequested; }
bool UserInput::isEscPressed() const { return escPressed; }

void UserInput::setWPressed(bool state) { wPressed = state; }
void UserInput::setAPressed(bool state) { aPressed = state; }
void UserInput::setSPressed(bool state) { sPressed = state; }
void UserInput::setDPressed(bool state) { dPressed = state; }
void UserInput::setMouseLeftPressed(bool state) { mouseLeftPressed = state; }
void UserInput::setMousePosition(int x, int y) {
    mouseX = x;
    mouseY = y;
}
void UserInput::setEscPressed(bool state) { escPressed = state; }

std::string UserInput::toString() const {
    std::stringstream oss;
    oss << "Quit: " << (quitRequested ? "1" : "0")
        << "; W:" << wPressed
        << "; A:" << aPressed
        << "; S:" << sPressed
        << "; D:" << dPressed
        << "; MouseLeft: " << mouseLeftPressed
        << "; Mouse: (" << mouseX << "," << mouseY << ")"
        << "; ObjectCount: " << objectCount;
    return oss.str();
}



