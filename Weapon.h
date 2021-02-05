//
// Created by pc on 01/2/2021.
//

#ifndef ANOTHER_TEST_WEAPON_H
#define ANOTHER_TEST_WEAPON_H

#include "Entity.h"
#include "vector"

class Weapon : public Entity {
public:
    Weapon();

    ~Weapon();

    void addAnimation(const char *texture);

    void AttackJ(int xpos, int ypos,int direction);

    void Update();

    int getAttackStatus(){
        return isAttacking;
    }

private:
    void ReleaseWhirlWind();

private:
    int direction;
    int isAttacking;
    int jStack;
    int damage;
    int currentAnimation;
    Uint32 lastAttackTime=0;
    Uint32 lastAnimationTime;
    Uint32 coolDown = 1500;
    Uint32 animationDelay;
    std::vector<SDL_Texture *> animations;

};


#endif //ANOTHER_TEST_WEAPON_H
