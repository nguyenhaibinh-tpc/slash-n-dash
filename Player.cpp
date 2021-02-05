//
// Created by pc on 31/1/2021.
//

#include "Player.h"
#include "Manager.h"

void Player::Update() {
    int xAdd = 0, yAdd = 0, xSub = 0, ySub = 0;
    for (int i = 0; i < 4; ++i) {
        if (direction[i]) {
            xAdd |= C[i] > 0;
            xSub |= C[i] < 0;
            yAdd |= D[i] > 0;
            ySub |= D[i] < 0;
        }
    }

    if(!willBeBlocked){
        destR.x += (xAdd - xSub) * speed;
        destR.y += (yAdd - ySub) * speed;
        hitBox.x = destR.x + hitBoxOffsetX;
        hitBox.y = destR.y + hitBoxOffsetY;
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
            currentAnimation = (currentAnimation +1 < stabAnimations.size() ? currentAnimation+1 : currentAnimation);
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
    } else if ((xAdd - xSub || yAdd - ySub) and !willBeBlocked) {
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
    int xAdd = 0, yAdd = 0, xSub = 0, ySub = 0;
    for (int i = 0; i < 4; ++i) {
        if (direction[i]) {
            xAdd |= C[i] > 0;
            xSub |= C[i] < 0;
            yAdd |= D[i] > 0;
            ySub |= D[i] < 0;
        }
    }

    ret.x = destR.x + hitBoxOffsetX + (xAdd - xSub) * speed;
    ret.y = destR.y + hitBoxOffsetY + (yAdd - ySub) * speed;

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

void Player::SetHitBox(int x, int y, int w, int h) {
    hitBoxOffsetX = x;
    hitBoxOffsetY = y;
    hitBox.h = h;
    hitBox.w = w;
}

void Player::AttackJ() {
    sword->AttackJ(destR.x, destR.y, (flip == SDL_FLIP_HORIZONTAL ? -1 : 1));
}

/** Setters Getters*/
/** Setters Getters*/
/** Setters Getters*/
/** Setters Getters*/

int Player::getCurrentAnimation() const {
    return currentAnimation;
}

void Player::setCurrentAnimation(int currentAnimation) {
    Player::currentAnimation = currentAnimation;
}

int Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(int speed) {
    Player::speed = speed;
}

const int *Player::getDirection() const {
    return direction;
}

SDL_Texture *Player::getObjTexture() const {
    return objTexture;
}

void Player::setObjTexture(SDL_Texture *objTexture) {
    Player::objTexture = objTexture;
}

const SDL_Rect &Player::getHitBox() const {
    return hitBox;
}

void Player::setHitBox(const SDL_Rect &hitBox) {
    Player::hitBox = hitBox;
}

SDL_RendererFlip Player::getFlip() const {
    return flip;
}

void Player::setFlip(SDL_RendererFlip flip) {
    Player::flip = flip;
}

Uint32 Player::getTimeSinceLastUpdate() const {
    return timeSinceLastUpdate;
}

void Player::setTimeSinceLastUpdate(Uint32 timeSinceLastUpdate) {
    Player::timeSinceLastUpdate = timeSinceLastUpdate;
}

int Player::getHitBoxOffsetX() const {
    return hitBoxOffsetX;
}

void Player::setHitBoxOffsetX(int hitBoxOffsetX) {
    Player::hitBoxOffsetX = hitBoxOffsetX;
}

int Player::getHitBoxOffsetY() const {
    return hitBoxOffsetY;
}

void Player::setHitBoxOffsetY(int hitBoxOffsetY) {
    Player::hitBoxOffsetY = hitBoxOffsetY;
}

int Player::getHealth() const {
    return health;
}

void Player::setHealth(int health) {
    Player::health = health;
}

Weapon *Player::getSword() const {
    return sword;
}

void Player::setSword(Weapon *sword) {
    Player::sword = sword;
}
