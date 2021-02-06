//
// Created by pc on 31/1/2021.
//

#include "Player.h"
#include "Manager.h"

void Player::moveLeft() {
    Flip(SDL_FLIP_HORIZONTAL);
    if (!isMovingLeft) {
        isMovingLeft = true;
        velocity -= speed;
    }
}

void Player::stopMovingLeft() {
    if (isMovingLeft) {
        isMovingLeft = false;
        velocity += speed;
    }
}

void Player::moveRight() {
    Flip(SDL_FLIP_NONE);
    if (!isMovingRight) {
        isMovingRight = true;
        velocity += speed;
    }
}

void Player::stopMovingRight() {
    if (isMovingRight) {
        isMovingRight = false;
        velocity -= speed;
    }
}

void Player::Update() {
    if (!willBeBlocked) {
        hitBox.x = (destR.x += velocity) + hitBoxOffsetX;
    }

    Uint32 currentTime = SDL_GetTicks();

    if (sword->getAttackStatus() == 1) {
        // is Q
        animationDelay = 50;
        if (currentStatus != 3)
            currentAnimation = 0;
        currentStatus = 3;
        if (currentTime >= lastAnimationTime + animationDelay) {
            objTexture = stabAnimations[currentAnimation];
            currentAnimation = (currentAnimation + 1 < stabAnimations.size() ? currentAnimation + 1 : currentAnimation);
            //currentAnimation = (currentAnimation + 1) % stabAnimations.size();
            lastAnimationTime = currentTime;
        }
    } else if (sword->getAttackStatus() == 2) {
        animationDelay = 200;
        if (currentStatus != 2)
            currentAnimation = 0;
        currentStatus = 2;
        // is QQQ
        //std::cout<<"Nice\n";
        //std::cout<<standingAnimations.size()<<"\n";
        if (currentTime >= lastAnimationTime + animationDelay) {
            objTexture = whirlwindAnimations[currentAnimation];
            currentAnimation = (currentAnimation + 1) % whirlwindAnimations.size();
            lastAnimationTime = currentTime;
        }
    } else if (velocity and !willBeBlocked) {
        animationDelay = 200;
        if (currentStatus != 1)
            currentAnimation = 0;
        currentStatus = 1;
        if (currentTime >= lastAnimationTime + animationDelay) {
            objTexture = movingAnimations[currentAnimation];
            currentAnimation = (currentAnimation + 1) % movingAnimations.size();
            lastAnimationTime = currentTime;
        }
        // is moving
    } else {
        animationDelay = 200;
        if (currentStatus != 0)
            currentAnimation = 0;
        currentStatus = 0;
        if (currentTime >= lastAnimationTime + animationDelay) {
            objTexture = standingAnimations[currentAnimation];
            currentAnimation = (currentAnimation + 1) % standingAnimations.size();
            lastAnimationTime = currentTime;
        }
        // is standing still
    }
}

void Player::Render() {
    SDL_RenderCopyEx(Manager::renderer, objTexture, nullptr, &destR, 0, nullptr, flip);
    sword->Render();
}

SDL_Rect Player::GetFakeHitBox() {
    SDL_Rect ret = hitBox;
    hitBox.x += velocity;
    return ret;
}

void Player::Flip(SDL_RendererFlip param) {
    flip = param;
}

void Player::addStandingAnimation(const char *texture) {
    standingAnimations.push_back(TextureLoader::LoadTexture(texture));
}

void Player::addMovingAnimation(const char *texture) {
    movingAnimations.push_back(TextureLoader::LoadTexture(texture));
}

void Player::addStabAnimation(const char *texture) {
    stabAnimations.push_back(TextureLoader::LoadTexture(texture));
}

void Player::addWhirlwindAnimation(const char *texture) {
    whirlwindAnimations.push_back(TextureLoader::LoadTexture(texture));
}

void Player::AddSpeed(int x, int y) {
    direction[x] = y;
}

void Player::setHitBox(int x, int y, int w, int h) {
    hitBoxOffsetX = x;
    hitBoxOffsetY = y;
    hitBox.h = h;
    hitBox.w = w;
}

void Player::AttackJ() {
    sword->AttackJ(destR.x, destR.y, (flip == SDL_FLIP_HORIZONTAL ? -1 : 1));
}

Weapon *Player::getSword() const {
    return sword;
}

