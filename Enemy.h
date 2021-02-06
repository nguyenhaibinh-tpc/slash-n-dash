//
// Created by pc on 05/2/2021.
//

#ifndef ANOTHER_TEST_ENEMY_H
#define ANOTHER_TEST_ENEMY_H

#include <vector>
#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy() : Entity() {

    }

    void Update();
    void Render();

    void Flip(SDL_RendererFlip param);
    void addStandingAnimation(const char* texture);
    void addMovingAnimation(const char* texture);
    void addAttackAnimation(const char* texture);

    void setHitBox(int x,int y,int w,int h);

private:
    int currentStatus;
    int currentAnimation;
    int speed = 1;
    int hitBoxOffsetX, hitBoxOffsetY;
    const int D[4] = {-1, 0, 1, 0};
    const int C[4] = {0, -1, 0, 1};
    int health;

    SDL_Rect hitBox;
    SDL_RendererFlip  flip = SDL_FLIP_NONE;
    Uint32 timeSinceLastUpdate;
    Uint32 lastAnimationTime;
    Uint32 animationDelay = 200;
    std::vector<SDL_Texture *> standingsAnimations;
    std::vector<SDL_Texture *> movingAnimations;
    std::vector<SDL_Texture *> attackingAnimations;

    //SimpleAI os;
};


#endif //ANOTHER_TEST_ENEMY_H
