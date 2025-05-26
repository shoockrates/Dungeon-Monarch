#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <thread>
#include <atomic>
#include "Room.h"

class SaveManager {
public:
    enum class Operation {
        Save,
        Load
    };

    SaveManager(SDL_Renderer* ren);
    ~SaveManager();

    void run(Operation op);

private:
    std::atomic<bool> done;

    std::thread workerThread;
    Operation currentOperation;

    SDL_Renderer* renderer;
    TTF_Font* font;

    void doSave();
    void doLoad();
    void handleEvents();
    void render(Operation op);
};
