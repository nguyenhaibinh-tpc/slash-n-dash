#include <iostream>
#include "Manager.h"


Manager *game;


int main(int argc, char *argv[]) {

    const int FPS = 244;
    const int frameDelay = 1000 / FPS;

    game = new Manager();

    game->init("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64 * 20, 64 * 16, false);

    Uint32 frameStart;
    int frameTime;

    while (game->running()) {
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay)
            SDL_Delay(frameDelay - frameTime);
    }

    game->clean();

    return 0;
}