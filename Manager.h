#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>

#include "Collision.h"
#include "Player.h"

class Manager {
public:
    Manager();
    ~Manager();

    void init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);

    void drawMenu();
    void handleMenuEvents();
    void updateMenu();
    bool running();
    void handleEvents();
    void update();
    void render();
    void clean();
    static SDL_Renderer *renderer;

//private:
    bool is_running = true;
    bool is_at_menu = true;
    bool is_over = false;
    SDL_Window *window;
};



