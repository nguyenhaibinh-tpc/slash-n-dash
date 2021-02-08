//
// Created by pc on 05/2/2021.
//

#ifndef ANOTHER_TEST_ENEMY_H
#define ANOTHER_TEST_ENEMY_H

#include <vector>
#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy() : Entity(){
        isMoving = true;
        isAttacking = false;
        isGivingDamage = false;
        isStanding = false;
        endOfEvent = true;
        attackDamage = 20;
        attackRange = 40;
        currentAnimation = 0;
        speed = 5;
        health = 50;
        animationDelay = 130;
    }

    int getAttackDamage() const;

    void setAttackDamage(int attackDamage);

    int getAttackRange() const;

    void setAttackRange(int attackRange);

    int getHealth() const;

    void setHealth(int health);;
    int getAttackFrame() const;

    void setAttackFrame(int attackFrame);
    ~Enemy(){};

    void Update();
    void Render();
    void addStandingAnimation(const char *texture);
    void addMovingAnimation(const char *texture);
    void addAttackAnimation(const char *texture);
    void setHitBox(int x, int y, int w, int h);
    void animationUpdate(std::vector<SDL_Texture*> &tmp, bool &cmd);
    void inSight(SDL_Rect x);
    void receiveDamage(int damage);
    void setDirection(int direction);

    bool getEndOfEvent();
    bool isDead();
    SDL_Rect getHitBox();

    bool enemyInRange;

//private:

    bool isMoving;
    bool isAttacking;
    bool isGivingDamage;
    bool isStanding;
    bool endOfEvent;

    int attackDamage;
    int attackRange;
    int attackFrame;

    int currentAnimation;
    int speed;
    int hitBoxOffsetX, hitBoxOffsetY;
    int health;
    int direction;

    SDL_Rect hitBox;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    Uint32 lastAnimationTime = 0;
    Uint32 animationDelay;
    std::vector<SDL_Texture *> standingsAnimations;
    std::vector<SDL_Texture *> movingAnimations;
    std::vector<SDL_Texture *> attackingAnimations;
};


#endif //ANOTHER_TEST_ENEMY_H
