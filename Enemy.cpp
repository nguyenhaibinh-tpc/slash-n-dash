//
// Created by pc on 05/2/2021.
//

#include "Enemy.h"
#include "Manager.h"


bool Enemy::getEndOfEvent() {
    return Enemy::endOfEvent;
}

SDL_Rect Enemy::getHitBox() {
    return Enemy::hitBox;
}

bool Enemy::isDead() {
    return Enemy::health <= 0;
}

void Enemy::setDirection(int direction) {
    Enemy::direction = direction;
}


void Enemy::animationUpdate(std::vector<SDL_Texture *> &tmp, bool &cmd) {
    objTexture = tmp[currentAnimation];
    isGivingDamage = isAttacking && currentAnimation == attackFrame;
    if (currentAnimation + 1 == tmp.size()) {
        cmd = false;
        endOfEvent = true;
        currentAnimation = 0;
        return;
    }
    currentAnimation += 1;
}

void Enemy::inSight(SDL_Rect x) {
    SDL_Rect tmp = hitBox;
    tmp.x += attackRange * direction;
    tmp.w += attackRange;
    if (Collision::StrictCollideRect(x, tmp)) {
        enemyInRange = true;
    }
}

void Enemy::Update() {
    if (endOfEvent) {
        if (enemyInRange)
            isAttacking = true;
        else
            isMoving = true;
        endOfEvent = false;
    }
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime >= lastAnimationTime + animationDelay) {
        if (isAttacking)
            animationUpdate(attackingAnimations, isAttacking);
        else if (isMoving) {
            animationUpdate(movingAnimations, isMoving);
            destR.x += speed * direction;
            hitBox.x = destR.x + hitBoxOffsetX;
        } else
            animationUpdate(standingsAnimations, isStanding);
        lastAnimationTime = currentTime;
    }
}

void Enemy::receiveDamage(int damage) {
    health -= damage;
}

void Enemy::Render() {
    //SDL_RenderCopy(Manager::renderer, objTexture, nullptr, &destR);
    SDL_RenderCopy(Manager::renderer, objTexture, nullptr, &destR);
}

void Enemy::addStandingAnimation(const char *texture) {
    standingsAnimations.push_back(TextureLoader::LoadTexture(texture));
}

void Enemy::addMovingAnimation(const char *texture) {
    movingAnimations.push_back(TextureLoader::LoadTexture(texture));
}

void Enemy::addAttackAnimation(const char *texture) {
    attackingAnimations.push_back(TextureLoader::LoadTexture(texture));
}

void Enemy::setHitBox(int x, int y, int w, int h) {
    hitBoxOffsetX = x;
    hitBoxOffsetY = y;
    hitBox.x = destR.x + hitBoxOffsetX;
    hitBox.y = destR.y + hitBoxOffsetY;
    hitBox.h = h;
    hitBox.w = w;
}

int Enemy::getAttackDamage() const {
    return attackDamage;
}

void Enemy::setAttackDamage(int attackDamage) {
    Enemy::attackDamage = attackDamage;
}

int Enemy::getAttackRange() const {
    return attackRange;
}

void Enemy::setAttackRange(int attackRange) {
    Enemy::attackRange = attackRange;
}

int Enemy::getHealth() const {
    return health;
}

void Enemy::setHealth(int health) {
    Enemy::health = health;
}

int Enemy::getAttackFrame() const {
    return attackFrame;
}

void Enemy::setAttackFrame(int attackFrame) {
    Enemy::attackFrame = attackFrame;
}
