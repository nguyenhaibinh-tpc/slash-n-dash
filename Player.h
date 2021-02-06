//
// Created by pc on 31/1/2021.
//

#ifndef ANOTHER_TEST_PLAYER_H
#define ANOTHER_TEST_PLAYER_H

#include "Entity.h"
#include "Weapon.h"

class Player : public Entity {
public:
    Player() : Entity(){

    };

    void Update();

    void Render();

    void Flip(SDL_RendererFlip param);

    void addStandingAnimation(const char *texture);
    void addMovingAnimation(const char *texture);
    void addStabAnimation(const char *texture);
    void addWhirlwindAnimation(const char *texture);

    void moveLeft();
    void moveRight();
    void stopMovingLeft();
    void stopMovingRight();

    void AddSpeed(int x, int y);

    void setHitBox(int x, int y, int w, int h);

    void setWillBeBlocked(bool tmp){
        willBeBlocked = tmp;
    }

    SDL_Rect GetFakeHitBox();

    void AttackJ();

private:
    bool isFalling;
    bool willBeBlocked;
    bool isMovingLeft;
    bool isMovingRight;

    int currentStatus;
    int currentAnimation;
    int speed = 1;
    int velocity;
    int hitBoxOffsetX, hitBoxOffsetY;
    const int D[4] = {-1, 0, 1, 0};
    const int C[4] = {0, -1, 0, 1};
    int direction[4];
    int health;

    SDL_Rect hitBox;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    Uint32 timeSinceLastUpdate;
    Uint32 lastAnimationTime;
    Uint32 animationDelay = 200;
    std::vector<SDL_Texture *> standingAnimations;
    std::vector<SDL_Texture *> movingAnimations;
    std::vector<SDL_Texture *> stabAnimations;
    std::vector<SDL_Texture *> whirlwindAnimations;

    Weapon *sword = new Weapon();

public:
    Weapon *getSword() const;
};


#endif //ANOTHER_TEST_PLAYER_H
