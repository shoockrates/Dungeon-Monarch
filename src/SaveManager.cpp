#include "../include/SaveManager.h"
#include <iostream>

SaveManager::SaveManager(SDL_Renderer* ren)
    : done(false), renderer(ren) {

    if (SDL_Init(SDL_INIT_VIDEO) == 0 || TTF_Init() == 0) {
        std::cerr << "SDL or TTF Init Failed: " << SDL_GetError() << std::endl;
    }

    font = TTF_OpenFont("assets/font.ttf", 48);
    if (!font) {
        std::cerr << "Failed to load font.\n";
    }
}

SaveManager::~SaveManager() {
    if (workerThread.joinable()) {
        workerThread.join();
    }
}

void SaveManager::run(Operation op) {

    done = false;
    currentOperation = op;

    if (op == Operation::Save) {
        workerThread = std::thread(&SaveManager::doSave, this);
    } else {
        workerThread = std::thread(&SaveManager::doLoad, this);
    }

    while (!done) {
        handleEvents();
        render(op);
        SDL_Delay(16);
    }

    workerThread.join();
}

void SaveManager::doSave() {
    
    // TODO: Actual save logic (write to file, serialize state, etc.)
    done = true;
}

void SaveManager::doLoad() {
    
    // TODO: Actual load logic (read file, restore game state, etc.)
    done = true;
}

void SaveManager::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            done = true;
        }
    }
}

void SaveManager::render(Operation op) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    const char* message = (op == Operation::Save) ? "Saving..." : "Loading...";
    size_t length = std::strlen(message);

    SDL_Color color = { 255, 255, 255, 255 };

    SDL_Surface* surface = TTF_RenderText_Solid(font, message, length, color);
    if (!surface) {
        std::cerr << "TTF_RenderUTF8_Solid error. (SaveManager)" << std::endl;
        SDL_RenderPresent(renderer);
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "SDL_CreateTextureFromSurface error: " << SDL_GetError() << std::endl;
        SDL_DestroySurface(surface);
        SDL_RenderPresent(renderer);
        return;
    }

    int texW = surface->w;
    int texH = surface->h;
    SDL_DestroySurface(surface);

    SDL_FRect dstRect;
    dstRect.x = Room::getWidth() * Room::getTileSize() / 2 - texW / 2;
    dstRect.y = Room::getHeight() * Room::getTileSize() / 2 - texH / 2;
    dstRect.w = texW;
    dstRect.h = texH;

    SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
    SDL_Delay(16);
}
