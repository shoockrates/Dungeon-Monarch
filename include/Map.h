#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <SDL3/SDL.h>

class Map{
    private:
        std::vector<std::vector<int>> map;
        void setMap(std::vector<std::vector<int>> map);

    public:
        Map();
        ~Map();
        std::vector<std::vector<int>> getMap();
        void loadMap(const std::string& filename);
        void renderMap(SDL_Renderer* renderer, SDL_Texture* groundTexture, SDL_Texture* wallTexture, int tileSize);
};

#endif // MAP_H
