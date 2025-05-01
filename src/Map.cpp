#include "../include/Map.h"
#include <fstream>


Map::Map(){}

Map::~Map(){}

void Map::setMap(std::vector<std::vector<int>> map) {
    this->map = map;
}

std::vector<std::vector<int>> Map::getMap() {
    return map;
}

void Map::loadMap(const std::string& filename) {
    std::vector<std::vector<int>> map;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char& c : line) {
            if (c == '0' || c == '1') {
                row.push_back(c - '0');
            }
        }
        if (!row.empty()) {
            map.push_back(row);
        }
    }
    setMap(map);
    file.close();
}

void Map::renderMap(SDL_Renderer* renderer, SDL_Texture* wallTexture, SDL_Texture* groundTexture, int tileSize) {
    for (size_t y = 0; y < this->map.size(); ++y) {
        for (size_t x = 0; x < this->map[y].size(); ++x) {
            SDL_FRect destRect = {
                static_cast<float>(x * tileSize),
                static_cast<float>(y * tileSize),
                static_cast<float>(tileSize),
                static_cast<float>(tileSize)
            };

            if (this->map[y][x] == 1) {
                SDL_RenderTexture(renderer, wallTexture, NULL, &destRect);
            } else {
                SDL_RenderTexture(renderer, groundTexture, NULL, &destRect);
            }
        }
    }
}
