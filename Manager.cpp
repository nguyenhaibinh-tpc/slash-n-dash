#include <cstring>
#include <random>
#include <chrono>
#include <algorithm>
#include "Manager.h"
#include "Character.h"
#include "Button.h"

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

SDL_Renderer *Manager::renderer = nullptr;

Entity *bg, *coin, *mnBg;
Button *yasuoButton, *pinkButton, *nikoButton, *playButton;

Entity *coinsNum, *waveText, *waveNum, *gameOver;

int score;
int wallet;
int killed;
int wave = -1;

std::vector<std::vector<int>> wavesMonster = {
        {5,  0},
        {15, 0},
        {0,  1},
        {5,  5},
        {50, 5},
        {40, 10},
        {50, 20}
};

std::vector<int> monsterLeft;


std::vector<Character *> allies, enemies;


Manager::Manager() {
    TTF_Init();
    is_running = true;
}

Manager::~Manager() {

}

void initYasuo(Character *&tmp, bool side) {
    tmp = new Character();

    tmp->loadMainTexture("../resources/yasuo_standing_0.png");
    tmp->setPosition(side ? -41 : 1100, 470);
    tmp->setDirection(side ? 1 : -1);
    tmp->setHitBox(92, 26, 40, 70);

    tmp->setBaseAttackDamage(20);
    tmp->setAttackRange(52);
    tmp->setAttackFrame(4);
    tmp->setHealth(42);
    tmp->setDamageReductionPercentage(10);
    tmp->setFlip(side ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
    tmp->setAnimationDelay(130);
    tmp->setPrice(4);

    for (int i:{0, 1, 2})
        tmp->addMovingAnimation(("../resources/yasuo_moving_" + std::to_string(i) + ".png").c_str());
    for (int i = 0; i < 6; ++i)
        tmp->addStandingAnimation(("../resources/yasuo_standing_" + std::to_string(i) + ".png").c_str());
    for (auto i:{0, 1, 2, 3, 4, 4, 2, 1})
        tmp->addAttackAnimation(("../resources/yasuo_stab_" + std::to_string(i) + ".png").c_str());
}

void initPinkSkull(Character *&tmp, bool side) {
    tmp = new Character();

    tmp->loadMainTexture("../resources/pink_standing_0.png");

    tmp->setPosition(side ? -41 : 1100, 470);
    tmp->setDirection(side ? 1 : -1);
    tmp->setHitBox(92, 26, 40, 70);
    tmp->setAttackFrame(3);

    tmp->setBaseAttackDamage(40);
    tmp->setAttackRange(35);
    tmp->setAttackFrame(3);
    tmp->setHealth(100);
    tmp->setDamageReductionPercentage(70);
    tmp->setFlip(side == 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
    tmp->setPrice(10);
    //tmp->setAnimationDelay(0);


    for (int i = 0; i < 4; ++i) {
        tmp->addStandingAnimation(("../resources/pink_standing_" + std::to_string(i) + ".png").c_str());
    }
    for (int i = 0; i < 6; ++i)
        tmp->addMovingAnimation(("../resources/pink_moving_" + std::to_string(i) + ".png").c_str());
    for (int i = 0; i < 5; ++i)
        tmp->addAttackAnimation(("../resources/pink_attack_" + std::to_string(i) + ".png").c_str());
}

void initGreenSkull(Character *&tmp, bool side) {
    tmp = new Character();

    tmp->loadMainTexture("../resources/green_standing_0.png");

    tmp->setPosition(side ? -41 : 1100, 470);
    tmp->setDirection(side ? 1 : -1);
    tmp->setHitBox(92, 26, 40, 70);
    tmp->setAttackFrame(3);

    tmp->setBaseAttackDamage(7);
    tmp->setAttackRange(50);
    tmp->setAttackFrame(3);
    tmp->setHealth(200);
    tmp->setDamageReductionPercentage(0);
    tmp->setAnimationDelay(40);
    tmp->setFlip(side == 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
    tmp->setPrice(16);


    for (int i = 0; i < 4; ++i) {
        tmp->addStandingAnimation(("../resources/green_standing_" + std::to_string(i) + ".png").c_str());
    }
    for (int i = 0; i < 6; ++i)
        tmp->addMovingAnimation(("../resources/green_moving_" + std::to_string(i) + ".png").c_str());
    for (int i = 0; i < 5; ++i)
        tmp->addAttackAnimation(("../resources/green_attack_" + std::to_string(i) + ".png").c_str());
}

void initNiko(Character *&tmp, bool side) {
    tmp = new Character();

    tmp->loadMainTexture("../resources/niko_attack_0.png");

    tmp->setPosition(side ? -41 : 1100, 470);
    tmp->setDirection(side ? 1 : -1);
    tmp->setHitBox(92, 26, 40, 70);
    tmp->setAttackFrame(3);

    tmp->setBaseAttackDamage(100);
    tmp->setAttackRange(30);
    tmp->setAttackFrame(13);
    tmp->setHealth(50);
    tmp->setDamageReductionPercentage(0);
    tmp->setAnimationDelay(70);
    tmp->setFlip(side == 1 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
    tmp->setPrice(16);


    for (int i = 0; i < 1; ++i)
        tmp->addStandingAnimation(("../resources/niko_attack_" + std::to_string(i) + ".png").c_str());
    for (int i = 0; i < 2; ++i)
        tmp->addMovingAnimation(("../resources/niko_moving_" + std::to_string(i) + ".png").c_str());
    for (int i = 0; i < 17; ++i)
        tmp->addAttackAnimation(("../resources/niko_attack_" + std::to_string(i) + ".png").c_str());
}

void Manager::init(const char *title, int x_pos, int y_pos, int width, int height, bool fullscreen) {
    is_at_menu = true;
    int is_fullscreen = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    if (!SDL_Init(SDL_INIT_EVERYTHING)) {
        window = SDL_CreateWindow(title, x_pos, y_pos, width, height, is_fullscreen);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }

    coinsNum = new Entity();
    waveText = new Entity();
    waveNum = new Entity();
    gameOver = new Entity();

    gameOver->loadMainTexture("../resources/over.png");
    gameOver->setDestR(512, -100, 256, 256);

    coin = new Entity();
    coin->loadMainTexture("../resources/coin.png");
    coin->setDestR(0, 645, 50, 50);

    waveText->setDestR(550, 650, 100, 50);
    coinsNum->setDestR(55, 650, 0, 40);
    waveNum->setDestR(620, 645, 0, 50);
    waveText->setObjTexture(TextureLoader::loadText("Wave", waveText->destR));

    yasuoButton = new Button();
    yasuoButton->setDestR(900, 630, 100, 70);
    yasuoButton->loadActiveTexture("../resources/button_icon/yasuo_active.png");
    yasuoButton->loadInactiveTexture("../resources/button_icon/yasuo.png");

    pinkButton = new Button();
    pinkButton->setDestR(1010, 630, 100, 70);
    pinkButton->loadInactiveTexture("../resources/button_icon/pink.png");
    pinkButton->loadActiveTexture("../resources/button_icon/pink_active.png");

    nikoButton = new Button();
    nikoButton->setDestR(1120, 630, 100, 70);
    nikoButton->loadInactiveTexture("../resources/button_icon/niko.png");
    nikoButton->loadActiveTexture("../resources/button_icon/niko_active.png");

    bg = new Entity();
    bg->loadMainTexture("../resources/background-1.png");
    bg->setPosition(0, 0);
    bg->setDestR(0, 0, 1280, 720);

    mnBg = new Entity();
    mnBg->loadMainTexture("../resources/long-background.png");
    mnBg->setSrcR(0, 0, 1280, 720);
    mnBg->setDestR(0, 0, 1280, 720);

    playButton = new Button();
    playButton->loadActiveTexture("../resources/button_icon/play-button.png");
    playButton->setIsActive(true);
    playButton->setDestR(546, 200, 187, 50);
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
    if(!is_over) {
        yasuoButton->handleEvents(event);
        pinkButton->handleEvents(event);
        nikoButton->handleEvents(event);
        playButton->handleEvents(event);
    }

    Uint32 ___ = SDL_GetTicks();

    if (yasuoButton->isHasOrder()) {
        wallet -= 13;
        allies.emplace_back();
        initYasuo(allies.back(), true);
        yasuoButton->timeSinceLastOrder = ___;
    }

    if (pinkButton->isHasOrder()) {
        wallet -= 30;
        allies.emplace_back();
        initPinkSkull(allies.back(), true);
        pinkButton->timeSinceLastOrder = ___;
    }

    if (nikoButton->isHasOrder()) {
        wallet -= 120;
        allies.emplace_back();
        initNiko(allies.back(), true);
        nikoButton->timeSinceLastOrder = ___;
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
                if (Collision::StrictCollideRect(ally->getHitBox(), tmp)) {
                    ally->receiveDamage(enemy->attackDamage);
                    enemy->setAttackDamage(enemy->getAttackDamage() * (100 - enemy->damageReductionPercentage) / 100);
                }
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
                if (Collision::StrictCollideRect(enemy->getHitBox(), tmp)) {
                    enemy->receiveDamage(ally->attackDamage);
                    ally->setAttackDamage(ally->getAttackDamage() * (100 - ally->damageReductionPercentage) / 100);
                }
            ally->isGivingDamage = false;
        }
    }

    for (int i = (int) allies.size() - 1; i >= 0; --i) {
        if (allies[i]->isDead())
            allies.erase(allies.begin() + i);
    }
    for (int i = (int) enemies.size() - 1; i >= 0; --i) {
        if (enemies[i]->isDead()) {
            enemies.erase(enemies.begin() + i);
            wallet += enemies[i]->getPrice();
            score += 15;
            killed--;
        } else if (enemies[i]->destR.x <= 0) {
            is_over = true;
            //is_running = false;
        }
    }

    if (!killed) {
        if (wave + 1 < (int) wavesMonster.size()) {
            score += wallet * 2;
            wave++;
            for (int i = 0; i < wavesMonster[wave].size(); ++i) {
                while (wavesMonster[wave][i]--) {
                    monsterLeft.push_back(i);
                    killed++;
                }
            }
            std::shuffle(monsterLeft.begin(), monsterLeft.end(), rng);

            wallet += allies.size() + 40;
            allies.clear();
        } else {
            is_running = false;
        }
    }

    if (monsterLeft.size() && (enemies.empty() || rng() % 1000 == 0)) {
        enemies.emplace_back();
        int type = monsterLeft.back();
        switch (type) {
            case 0:
                initPinkSkull(enemies.back(), false);
                break;
            case 1:
                initGreenSkull(enemies.back(), false);
                break;
            default:
                break;
        }
        monsterLeft.pop_back();
    }
    Uint32 currentTime = SDL_GetTicks();
    yasuoButton->setIsActive(wallet >= 13 && currentTime >= yasuoButton->timeSinceLastOrder + 1000);
    pinkButton->setIsActive(wallet >= 30 && currentTime >= pinkButton->timeSinceLastOrder + 1000);
    nikoButton->setIsActive(wallet >= 120 && currentTime >= nikoButton->timeSinceLastOrder + 1000);
}


void Manager::update() {
    if (is_over) {
        if (gameOver->destR.y < 200) {
            gameOver->destR.y++;
        }
    } else {
        for (auto enemy:enemies)
            enemy->Update();
        for (auto ally:allies)
            ally->Update();
        coinsNum->setObjTexture(TextureLoader::loadNumber(wallet, coinsNum->destR, 30));
        waveNum->setObjTexture(TextureLoader::loadNumber(wave + 1, waveNum->destR, 30));
    }
}

void Manager::render() {
    SDL_RenderClear(renderer);
    bg->Render();
    for (auto &enemy:enemies)
        enemy->Render();
    for (auto &ally:allies)
        ally->Render();

    yasuoButton->Render();
    pinkButton->Render();
    nikoButton->Render();

    coin->Render();
    coinsNum->Render();
    waveText->Render();
    waveNum->Render();

    if (is_over)
        gameOver->Render();

    SDL_RenderPresent(renderer);
}

void Manager::clean() {
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

bool Manager::running() {
    return is_running;
}

void Manager::handleMenuEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
    }

    playButton->handleEvents(event);
}

void Manager::drawMenu() {
    SDL_RenderClear(renderer);
    mnBg->SrcRender();
    playButton->Render();
    SDL_RenderPresent(renderer);
}

int decay;

void Manager::updateMenu() {
    if (playButton->isHasOrder()) {
        is_at_menu = false;
    }
    ++decay %= 3;
    if (!decay) {
        mnBg->srcR.x++;
        if (mnBg->srcR.x + mnBg->srcR.w == 2560)
            mnBg->srcR.x = 0;
    }
}
