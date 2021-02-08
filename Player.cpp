//
// Created by pc on 31/1/2021.
//

#include "Player.h"
#include "Manager.h"

void Player::animationUpdate(std::vector<SDL_Texture *> &tmp, bool &cmd) {
    objTexture = tmp[currentAnimation];
    isGivingDamage = isAttacking && currentAnimation == 4;
    if (currentAnimation + 1 == tmp.size()) {
        cmd = false;
        endOfEvent = true;
        currentAnimation = 0;
        return;
    }
    currentAnimation += 1;
}

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
    if (endOfEvent) {
        if (enemyInRange)
            isAttacking = true;
        else
            isMovingRight = true;
        endOfEvent = false;
    }

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime >= lastAnimationTime + animationDelay) {
        if(isAttacking)
            animationUpdate(stabAnimations, isAttacking);
        else if(isMovingRight){
            animationUpdate(movingAnimations,isMovingRight);
            destR.x += 10;
            hitBox.x = destR.x + hitBoxOffsetX;
        } else
            animationUpdate(standingAnimations, isStanding);
        lastAnimationTime = currentTime;
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

void Player::setHitBox(int x, int y, int w, int h) {
    hitBoxOffsetX = x;
    hitBoxOffsetY = y;
    hitBox.h = h;
    hitBox.w = w;
    hitBox.x = destR.x + hitBoxOffsetX;
    hitBox.y = destR.y + hitBoxOffsetY;
}

void Player::AttackJ() {
    sword->AttackJ(destR.x, destR.y, (flip == SDL_FLIP_HORIZONTAL ? -1 : 1));
}

Weapon *Player::getSword() const {
    return sword;
}

SDL_Rect Player::getHitBox() {
    return hitBox;
}

void Player::receiveDamage(int damage) {
    health -= damage;
}
