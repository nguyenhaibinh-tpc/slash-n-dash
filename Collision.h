//
// Created by pc on 27/1/2021.
//

#ifndef ANOTHER_TEST_COLLISION_H
#define ANOTHER_TEST_COLLISION_H

#include "SDL.h"
#include "iostream"

class Collision {
public:
    static bool StrictCollideRect(SDL_Rect a, SDL_Rect b);
    static bool PairCollide(std::pair<int,int> a, std::pair<int,int> b);

    static bool CollideByArea(SDL_Rect a, SDL_Rect b);
};


#endif //ANOTHER_TEST_COLLISION_H
