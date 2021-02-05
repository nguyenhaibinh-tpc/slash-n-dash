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

    void AddSpeed(int x, int y);

    void SetHitBox(int x, int y, int w, int h);

    void setWillBeBlocked(bool tmp){
        willBeBlocked = tmp;
    }

    SDL_Rect GetFakeHitBox();

    void AttackJ();

private:
    bool willBeBlocked = false;
    int currentStatus;
    int currentAnimation;
    int speed = 1;
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

    void setSword(Weapon *sword);

    int getHealth() const;

    void setHealth(int health);

    int getHitBoxOffsetX() const;

    void setHitBoxOffsetX(int hitBoxOffsetX);

    int getHitBoxOffsetY() const;

    void setHitBoxOffsetY(int hitBoxOffsetY);

    int getCurrentAnimation() const;

    void setCurrentAnimation(int currentAnimation);

    int getSpeed() const;

    void setSpeed(int speed);

    const int *getDirection() const;

    SDL_Texture *getObjTexture() const;

    void setObjTexture(SDL_Texture *objTexture);

    const SDL_Rect &getHitBox() const;

    void setHitBox(const SDL_Rect &hitBox);

    SDL_RendererFlip getFlip() const;

    void setFlip(SDL_RendererFlip flip);

    Uint32 getTimeSinceLastUpdate() const;

    void setTimeSinceLastUpdate(Uint32 timeSinceLastUpdate);
};


#endif //ANOTHER_TEST_PLAYER_H
