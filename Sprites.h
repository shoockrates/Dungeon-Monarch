#ifndef SPRITES_H
#define SPRITES_H

#include "SDL3/SDL.h"

/*
* The purpose of this file is to store all textures that we might need, in one place
* Feel free to add more textures if needed
*/


struct Sprites {
    SDL_Texture* playerTexture = nullptr;
    SDL_Texture* enemyTexture = nullptr;
    SDL_Texture* tileTexture = nullptr;
    SDL_Texture* bulletTexture = nullptr;
   
};

#endif