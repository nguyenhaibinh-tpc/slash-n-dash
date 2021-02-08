#include <cstring>
#include "Manager.h"
#include "Enemy.h"

#include "bits/stdc++.h"


SDL_Renderer *Manager::renderer = nullptr;

Entity *bg;

Enemy *go, goo;


std::vector<Enemy *> allies, enemies;


Manager::Manager() {
    is_running = true;
}

Manager::~Manager() {

}

void initYasuo(Enemy *&tmp, bool side) {
    tmp = new Enemy();

    tmp->loadMainTexture("../resources/yasuo_standing_0.png");
    tmp->setPosition(side ? -41 : 1100, 533);
    tmp->setDirection(side ? 1 : -1);
    tmp->setHitBox(92, 26, 40, 70);

    tmp->setAttackDamage(30);
    tmp->setAttackRange(52);
    tmp->setAttackFrame(4);
    tmp->setHealth(42);

    for (int i:{0, 1, 2})
        tmp->addMovingAnimation(("../resources/yasuo_moving_" + std::to_string(i) + ".png").c_str());
    for (int i = 0; i < 6; ++i)
        tmp->addStandingAnimation(("../resources/yasuo_standing_" + std::to_string(i) + ".png").c_str());
    for (auto i:{0, 1, 2, 3, 4, 4, 2, 1})
        tmp->addAttackAnimation(("../resources/yasuo_stab_" + std::to_string(i) + ".png").c_str());
}

void initPinkSkull(Enemy *&tmp, bool side) {
    tmp = new Enemy();

    tmp->loadMainTexture("../resources/pink_standing_0.png");

    tmp->setPosition(side ? -41 : 1100, 533);
    tmp->setDirection(side ? 1 : -1);
    tmp->setHitBox(92, 26, 40, 70);
    tmp->setAttackFrame(3);

    tmp->setAttackDamage(20);
    tmp->setAttackRange(40);
    tmp->setAttackFrame(3);
    tmp->setHealth(100);

    for (int i = 0; i < 4; ++i) {
        tmp->addStandingAnimation(("../resources/pink_standing_" + std::to_string(i) + ".png").c_str());
    }
    for (int i = 0; i < 6; ++i)
        tmp->addMovingAnimation(("../resources/pink_moving_" + std::to_string(i) + ".png").c_str());
    for (int i = 0; i < 5; ++i)
        tmp->addAttackAnimation(("../resources/pink_attack_" + std::to_string(i) + ".png").c_str());
}

void Manager::init(const char *title, int x_pos, int y_pos, int width, int height, bool fullscreen) {
    int is_fullscreen = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    if (!SDL_Init(SDL_INIT_EVERYTHING)) {
        window = SDL_CreateWindow(title, x_pos, y_pos, width, height, is_fullscreen);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }

    bg = new Entity();
    bg->loadMainTexture("../resources/background.png");
    bg->setPosition(0, 0);
    bg->setDestR(0, 0, 1280, 720);


    allies.emplace_back();
    initYasuo(allies.back(), true);

    enemies.emplace_back();
    initPinkSkull(enemies.back(), false);
}

void Manager::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
    }

    for (auto &enemy:enemies) {
        if (enemy->getEndOfEvent()) {
            enemy->enemyInRange = false;
            for (auto &ally:allies)
                enemy->inSight(ally->getHitBox());
        }
        if (enemy->isGivingDamage) {
            SDL_Rect tmp = enemy->hitBox;
            tmp.x += enemy->attackRange * enemy->direction;
            tmp.w += enemy->attackRange;
            for (auto &ally:allies)
                if (Collision::StrictCollideRect(ally->getHitBox(), tmp))
                    ally->receiveDamage(enemy->attackDamage);
            enemy->isGivingDamage = false;
        }
    }

    for (auto &ally:allies) {
        if (ally->getEndOfEvent()) {
            ally->enemyInRange = false;
            for (auto &enemy:enemies)
                ally->inSight(enemy->getHitBox());
        }
        if (ally->isGivingDamage) {
            SDL_Rect tmp = ally->hitBox;
            tmp.x += ally->attackRange * ally->direction;
            tmp.w += ally->attackRange;

            for (auto &enemy:enemies)
                if (Collision::StrictCollideRect(enemy->getHitBox(), tmp))
                    enemy->receiveDamage(ally->attackDamage);
            ally->isGivingDamage = false;
        }
    }

    for(auto i:allies) std::cout<<i->getHealth()<<" "; std::cout<<"\n";
    for(auto i:enemies) std::cout<<i->getHealth()<<" "; std::cout<<"\n\n";

    for (int i = allies.size() - 1; i >= 0; --i) {
        if(allies[i]->isDead())
            allies.erase(allies.begin()+i);
    }
    for (int i = enemies.size() - 1; i >= 0; --i) {
        if(enemies[i]->isDead())
            enemies.erase(enemies.begin()+i);
    }

    if(enemies.empty()){
        enemies.emplace_back();
        initPinkSkull(enemies.back(), false);
    }

    if(allies.empty()){
        allies.emplace_back();
        initYasuo(allies.back(),true);
    }
}


void Manager::update() {
    for (auto enemy:enemies)
        enemy->Update();
    for (auto ally:allies)
        ally->Update();
}

void Manager::render() {
    SDL_RenderClear(renderer);
    bg->Render();
    for (auto &enemy:enemies)
        enemy->Render();
    for (auto &ally:allies)
        ally->Render();
    SDL_RenderPresent(renderer);
}

void Manager::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

bool Manager::running() {
    return is_running;
}
