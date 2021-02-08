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
    void setHitBox(int x, int y, int w, int h);
    void receiveDamage(int damage);
    void animationUpdate(std::vector<SDL_Texture *> &tmp, bool &cmd);

    int getHealth() {
        return health;
    }

    void setWillBeBlocked(bool tmp){
        willBeBlocked = tmp;
    }
    bool isDead(){
        return health <= 0;
    }

    SDL_Rect GetFakeHitBox();

    void AttackJ();

private:
    bool endOfEvent;
    bool isAttacking;
    bool isGivingDamage;
    bool isFalling;
    bool isStanding;
    bool willBeBlocked;
    bool isMovingLeft;
    bool isMovingRight;
    bool enemyInRange;

    int currentStatus;
    int currentAnimation;
    int speed = 1;
    int velocity;
    int hitBoxOffsetX, hitBoxOffsetY;
    int health = 70;

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

    SDL_Rect getHitBox();
};


#endif //ANOTHER_TEST_PLAYER_H
