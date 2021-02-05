//
// Created by pc on 25/1/2021.
//

#include "Map.h"
#include <cstring>
#include <random>
#include <chrono>

//std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
std::mt19937 rng(1012);

int tmp[16][20]={
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};

int rnd(int l, int r) {
    return l + rng() % (r - l + 1);
}

Map::Map(int width, int height) {
    dirt = TextureLoader::LoadTexture(R"(C:\Users\pc\CLionProjects\another-test\resources\dirt.png)");
    water = TextureLoader::LoadTexture(R"(C:\Users\pc\CLionProjects\another-test\resources\water.png)");
    grass = TextureLoader::LoadTexture(R"(C:\Users\pc\CLionProjects\another-test\resources\grass.png)");

    Map::height = height;
    Map::width = width;

    schemeMap.resize(Map::height);
    for (auto &row:schemeMap)
        row.resize(Map::width);

    srcR.x = srcR.y = 0;
    srcR.w = srcR.h = 1000;
    destR.w = destR.h = 64;

    for (int row = 0; row < Map::height; ++row) {
        for (int column = 0; column < Map::width; ++column) {
            //schemeMap[row][column] = rnd(0, 2);
            schemeMap[row][column] = tmp[row][column];
        }
    }

    //schemeMap[10][10] = 0;



    loadMap();
}

Map::~Map() {

}

void Map::loadMap() {

}

void Map::drawMap() {
    for (int row = 0; row < 16; ++row) {
        for (int column = 0; column < 20; ++column) {
            destR.y = row * 64, destR.x = column * 64;
            switch (schemeMap[row][column]) {
                case 0:
                    TextureLoader::Draw(dirt, srcR, destR);
                    break;
                case 1:
                    TextureLoader::Draw(water, srcR, destR);
                    break;
                case 2:
                    TextureLoader::Draw(grass, srcR, destR);
                    break;

                default:
                    break;
            }

        }
    }
}
