#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <SDL3/SDL.h>

std::vector<std::vector<int>> loadMap(const std::string& filename);
void renderMap(SDL_Renderer* renderer, SDL_Texture* groundTexture, SDL_Texture* wallTexture, const std::vector<std::vector<int>>& map, int tileSize);

#endif // MAP_H
