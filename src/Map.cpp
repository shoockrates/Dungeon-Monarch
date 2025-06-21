#include "../include/Map.h"
#include <fstream>
#include <iostream>


Map::Map(){}

Map::~Map(){}

void Map::setMap(std::vector<std::vector<int>  > map) {
    this->map = map;
}

std::vector<std::vector<int> > Map::getMap() {
    return map;
}

void Map::loadMap(const std::string& filename, std::vector<Enemy>& enemies, int tileSize) {
    std::vector<std::vector<int>> map;
    std::ifstream file(filename);
    std::string line;
    int row = 0;

    while (std::getline(file, line)) {
        std::vector<int> mapRow;
        for (size_t col = 0; col < line.size(); ++col) {
            char c = line[col];
            if (c >= '0' && c <= '3') {
                int tile = c - '0';
                mapRow.push_back(tile);

                if (tile == 2) {
                    int x = col * tileSize;
                    int y = row * tileSize;
                    enemies.push_back(Enemy("Zombie", 50, 10, 10, x, y));
                } else if (tile == 3) {
                    doorX = col * tileSize;
                    doorY = row * tileSize;
                }
            }
        }
        if (!mapRow.empty()) {
            map.push_back(mapRow);
        }
        row++;
    }
    this->map = map;
}

void Map::renderMap(SDL_Renderer* renderer, SDL_Texture* wallTexture, SDL_Texture* groundTexture, SDL_Texture* doorTexture, int tileSize) {
    for (size_t y = 0; y < this->map.size(); ++y) {
        for (size_t x = 0; x < this->map[y].size(); ++x) {
            SDL_FRect destRect = {
                static_cast<float>(x * tileSize),
                static_cast<float>(y * tileSize),
                static_cast<float>(tileSize),
                static_cast<float>(tileSize)
            };

            if (this->map[y][x] == 1) {
                // Render wall texture
                SDL_RenderTexture(renderer, wallTexture, NULL, &destRect);
            } 
            else if (this->map[y][x] == 0) {
                // Render ground texture
                SDL_RenderTexture(renderer, groundTexture, NULL, &destRect);
            }
            else if (this->map[y][x] == 3) {
                SDL_RenderTexture(renderer, doorTexture, NULL, &destRect);
            }

        }
    }
}
