//
// Created by pc on 01/2/2021.
//

#include "Weapon.h"
#include <stdlib.h>
#include <iostream>

Weapon::Weapon() {
    destR.w = destR.h = 128;
    destR.w = 90;
}

void Weapon::addAnimation(const char *texture) {
    animations.emplace_back(TextureLoader::LoadTexture(texture));
    //exit(0);
}

void Weapon::ReleaseWhirlWind() {

}

void Weapon::Update() {
    if (isAttacking == 2) {
        //std::cout<<"Updating weapon\n";
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime >= lastAnimationTime + animationDelay) {
            animationDelay = (currentTime - lastAttackTime) / 40;
            destR.x += 5 * direction;
            //destR.y += 5;
            if (currentTime >= lastAttackTime + coolDown) {
                isAttacking = false;
                currentAnimation = 0;
                objTexture = nullptr;
            } else {
                currentAnimation = (currentAnimation + 1) % animations.size();
                objTexture = animations[currentAnimation];
            }
            lastAnimationTime = currentTime;
        }
    } else if (isAttacking == 1) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime >= lastAttackTime + coolDown / 2) {
            isAttacking = false;
            currentAnimation = 0;
            objTexture = nullptr;
        }
    }
}

void Weapon::AttackJ(int xpos, int ypos, int direction) {
    Uint32 currentTime = SDL_GetTicks();
    //std::cout << currentTime << " " << lastAttackTime << " " << coolDown << "\n";
    if (!lastAttackTime or currentTime >= lastAttackTime + coolDown) {
        Weapon::direction = direction;
        destR.x = xpos;
        destR.y = ypos - 25;
        std::cout << "Attacking\n";
        //isAttacking = 2;
        //jStack = 0;
        lastAnimationTime = currentTime;
        //ReleaseWhirlWind();
        animationDelay = 30;

        jStack = (jStack + 1) % 3;
        if (jStack) {
            isAttacking = 1;
        } else {
            isAttacking = 2;
        }

        lastAttackTime = currentTime;
    }
}