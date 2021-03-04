//
// Created by pc on 05/2/2021.
//

#include "Character.h"
#include "Manager.h"


bool Character::getEndOfEvent() {
    return Character::endOfEvent;
}

SDL_Rect Character::getHitBox() {
    return Character::hitBox;
}

bool Character::isDead() {
    return Character::health <= 0;
}

void Character::setDirection(int direction) {
    Character::direction = direction;
}


void Character::animationUpdate(std::vector<SDL_Texture *> &tmp, bool &cmd) {
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

void Character::inSight(SDL_Rect x) {
    SDL_Rect tmp = hitBox;
    tmp.x += attackRange * direction;
    tmp.w += attackRange;
    if (Collision::StrictCollideRect(x, tmp)) {
        enemyInRange = true;
    }
}

void Character::Update() {
    if (endOfEvent) {
        if (enemyInRange) {
            isAttacking = true;
            attackDamage = baseAttackDamage;
        }
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

void Character::receiveDamage(int damage) {
    health -= damage;
}

void Character::setFlip(SDL_RendererFlip flip) {
    Character::flip = flip;
}

void Character::Render() {
    //SDL_RenderCopy(Manager::renderer, objTexture, nullptr, &destR);
    //SDL_RenderCopy(Manager::renderer, objTexture, nullptr, &destR);
    SDL_RenderCopyEx(Manager::renderer, objTexture, nullptr, &destR, 0, nullptr, flip);
}

void Character::addStandingAnimation(const char *texture) {
    standingsAnimations.push_back(TextureLoader::LoadTexture(texture));
}

void Character::addMovingAnimation(const char *texture) {
    movingAnimations.push_back(TextureLoader::LoadTexture(texture));
}

void Character::addAttackAnimation(const char *texture) {
    attackingAnimations.push_back(TextureLoader::LoadTexture(texture));
}

void Character::setHitBox(int x, int y, int w, int h) {
    hitBoxOffsetX = x;
    hitBoxOffsetY = y;
    hitBox.x = destR.x + hitBoxOffsetX;
    hitBox.y = destR.y + hitBoxOffsetY;
    hitBox.h = h;
    hitBox.w = w;
}

int Character::getAttackDamage() const {
    return attackDamage;
}

void Character::setAttackDamage(int attackDamage) {
    Character::attackDamage = attackDamage;
}

int Character::getAttackRange() const {
    return attackRange;
}

void Character::setAttackRange(int attackRange) {
    Character::attackRange = attackRange;
}

int Character::getHealth() const {
    return health;
}

void Character::setHealth(int health) {
    Character::health = health;
}

int Character::getAttackFrame() const {
    return attackFrame;
}

void Character::setAttackFrame(int attackFrame) {
    Character::attackFrame = attackFrame;
}

int Character::getBaseAttackDamage() const {
    return baseAttackDamage;
}

void Character::setBaseAttackDamage(int baseAttackDamage) {
    Character::baseAttackDamage = baseAttackDamage;
}

int Character::getDamageReductionPercentage() const {
    return damageReductionPercentage;
}

void Character::setDamageReductionPercentage(int damageReductionPercentage) {
    Character::damageReductionPercentage = damageReductionPercentage;
}

Uint32 Character::getAnimationDelay() const {
    return animationDelay;
}

void Character::setAnimationDelay(Uint32 animationDelay) {
    Character::animationDelay = animationDelay;
}

int Character::getPrice() const {
    return price;
}

void Character::setPrice(int price) {
    Character::price = price;
}
