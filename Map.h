//
// Created by pc on 25/1/2021.
//

#ifndef ANOTHER_TEST_MAP_H
#define ANOTHER_TEST_MAP_H

#include "SDL.h"
#include "TextureLoader.h"
#include "vector"
#include "Entity.h"

class Map {
public:
    Map(int width, int height);
    ~Map();
    void loadMap();
    void drawMap();

//private:
    SDL_Rect srcR, destR;
    SDL_Texture *dirt;
    SDL_Texture *grass;
    SDL_Texture *water;

    std::vector<std::vector<int>> schemeMap;
    //std::vector<std::vector<Entity>> entityMap;
    int width, height;
};


#endif //ANOTHER_TEST_MAP_H
