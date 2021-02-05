#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

#include "Map.h"
#include "Collision.h"
#include "Player.h"

class Manager {
public:
    Manager();
    ~Manager();

    void init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
    bool running();
    void handleEvents();
    void update();
    void render();
    void clean();
    static SDL_Renderer *renderer;

private:
    bool is_running = true;
    SDL_Window *window;
};



