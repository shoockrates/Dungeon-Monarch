#include "../../include/UI/UIElement.h"
#include <iostream>
#include <SDL3/SDL.h>

UIElement::UIElement(SDL_Renderer* ren, float x, float y, float w, float h)
    : renderer(ren), texture(nullptr) {

    textColor.r = 255;
    textColor.g = 0;
    textColor.b = 0;
    textColor.a = 255; 

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    font = TTF_OpenFont("assets/font.ttf", 24);
    if (!font) {
        std::cout << "Failed to load font: " << "\n";
    }
}

UIElement::~UIElement() {
    cleanUp();
}

void UIElement::update(float x, float y, int hp) {
    rect.x = x;
    rect.y = y;

    std::string newInfo = std::to_string(hp);
    if (newInfo != displayInfo || texture == nullptr) {
        displayInfo = newInfo;

        if (texture) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }

        SDL_Surface* textSurface = TTF_RenderText_Solid(font, displayInfo.c_str(), displayInfo.length(), textColor);
        if (!textSurface) {
            std::cout << "Text surface error " << "\n";
            return;
        }

        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_DestroySurface(textSurface);

        if (!texture) {
            //std::cout << "Texture is NULL: " << SDL_GetError() << std::endl;
        }
    }
}

void UIElement::render() {
    if (!texture || !renderer) return;

    float texWidth, texHeight;
    SDL_GetTextureSize(texture, &texWidth, &texHeight);

    if (texWidth <= 0 || texHeight <= 0) {
        std::cout << "Invalid texture dimensions: " << texWidth << "x" << texHeight << std::endl;
        return;
    }

    SDL_FRect destRect = {
        rect.x + (rect.w - texWidth) / 2.0f,
        rect.y - texHeight - 5.0f,
        static_cast<float>(texWidth),
        static_cast<float>(texHeight)
    };

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_RenderTexture(renderer, texture, NULL, &destRect);
}

void UIElement::cleanUp() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

