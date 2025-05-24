#include "../include/Renderer.h"

int Renderer::objectCount = 0;

Renderer::Renderer(int roomWidth, int roomHeight, int tileSize) {
    init(roomWidth, roomHeight, tileSize);
    objectCount++;
}

Renderer::Renderer() {
    objectCount++;
}

Renderer::~Renderer() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    objectCount--;
}

SDL_Window* Renderer::getWindow() const {
    return window;
}

SDL_Renderer* Renderer::getRenderer() const {
    return renderer;
}

int Renderer::getObjectCount() {
    return objectCount;
}

SDL_Renderer* Renderer::getSDLRenderer() {
    return renderer;
}


void Renderer::setWindow(SDL_Window* newWindow) {
    window = newWindow;
}

void Renderer::setRenderer(SDL_Renderer* newRenderer) {
    renderer = newRenderer;
}

void Renderer::init(int roomWidth, int roomHeight, int tileSize) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Init failed: %s", SDL_GetError());
        throw std::runtime_error("SDL_Init failed");
    }

    window = SDL_CreateWindow("Dungeon Monarch", roomWidth * tileSize, roomHeight * tileSize, SDL_WINDOW_OPENGL);
    if (!window) {
        throw std::runtime_error("Window creation failed");
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        SDL_DestroyWindow(window);
        throw std::runtime_error("Renderer creation failed");
    }
}

SDL_Texture* Renderer::loadSprite(const std::string& path) {
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (!surface) {
        SDL_Log("Failed to load BMP: %s", SDL_GetError());
        throw std::runtime_error("BMP load failed: " + path);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!texture) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        throw std::runtime_error("Texture creation failed: " + path);
    }

    return texture;
}

SDL_Texture* Renderer::loadSpritePNG(const std::string& path) {
    // Load image using SDL_image
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        SDL_Log("Failed to load image %s.", path.c_str());
        return nullptr;
    }

    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Failed to create texture from %s: %s", path.c_str(), SDL_GetError());
        SDL_DestroySurface(surface);
        return nullptr;
    }

    // Clean up surface after creating texture
    SDL_DestroySurface(surface);
    return texture;
}


void Renderer::drawRoomTiled(SDL_Texture* tileTexture, int roomWidth, int roomHeight, int tileSize) {
    for (int row = 0; row < roomHeight; ++row) {
        for (int col = 0; col < roomWidth; ++col) {
            int x = col * tileSize;
            int y = row * tileSize;
            drawSprite(tileTexture, x, y, tileSize, tileSize);
        }
    }
}

void Renderer::drawSprite(SDL_Texture* texture, int x, int y, int width, int height) {
    SDL_FRect dstRect = { static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height) };
    SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}

void Renderer::clear() {
    SDL_RenderClear(renderer);
}

std::string Renderer::toString() const {
    std::stringstream oss;
    oss << "Window: " << (window ? "ok" : "null")
        << "; Renderer: " << (renderer ? "ok" : "null")
        << "; ObjectCount: " << objectCount;
    return oss.str();
}


