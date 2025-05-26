#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <SDL3/SDL.h>
#include "./entities/Enemy.h"


class Map{
    private:
        std::vector<std::vector<int> > map;
        void setMap(std::vector<std::vector<int> > map);

    public:
        int doorX, doorY;

        Map();
        ~Map();
        std::vector<std::vector<int> > getMap();
        void loadMap(const std::string& filename, std::vector<Enemy>& enemies, int tileSize);
        void renderMap(SDL_Renderer* renderer, SDL_Texture* wallTexture, SDL_Texture* groundTexture, SDL_Texture* doorTexture, int tileSize);
        void printMap();
};

#endif // MAP_H
