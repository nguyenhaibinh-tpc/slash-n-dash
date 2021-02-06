#include <cstring>
#include "Manager.h"


SDL_Renderer *Manager::renderer = nullptr;
Map *mp;
Player *yasuo;

Entity *bg;


Manager::Manager() {
    is_running = true;
}

Manager::~Manager() {

}

bool noCollision() {
    auto fake = yasuo->GetFakeHitBox();
    for (int row = 0; row < 16; ++row) {
        for (int column = 0; column < 20; ++column)
            if (!mp->schemeMap[row][column]) {
                SDL_Rect tmp = mp->destR;
                tmp.y = row * 64, tmp.x = column * 64;
                /**
                std::cout<<fake.x<<" ,"<<fake.y<<"\n";
                std::cout<<fake.x<<" ,"<<fake.y+fake.h<<"\n";
                std::cout<<fake.x+fake.w<<" ,"<<fake.y+fake.h<<"\n";
                std::cout<<fake.x+fake.w<<" ,"<<fake.y<<"\n";
                std::cout<<fake.x<<" ,"<<fake.y<<"\n";

                std::cout<<"\n";

                std::cout<<tmp.x<<" ,"<<tmp.y<<"\n";
                std::cout<<tmp.x<<" ,"<<tmp.y+tmp.h<<"\n";
                std::cout<<tmp.x+tmp.w<<" ,"<<tmp.y+tmp.h<<"\n";
                std::cout<<tmp.x+tmp.w<<" ,"<<tmp.y<<"\n";
                std::cout<<tmp.x<<" ,"<<tmp.y<<"\n";

                std::cout<<"\n";
                 */

                if (Collision::StrictCollideRect(fake, tmp))
                    return 0;

            }
    }
    return 1;
}

bool noOutOfBound() {
    auto fake = yasuo->GetFakeHitBox();
    return fake.x >= 0 && fake.y >= 0;
}


void initYasuo(){
    yasuo = new Player();
    yasuo->loadMainTexture(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_norm_0.png)");
    yasuo->setPosition(-41,533);


    yasuo->addMovingAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_moving_0.png)");
    yasuo->addMovingAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_moving_1.png)");
    yasuo->addMovingAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_moving_2.png)");

    yasuo->addStandingAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_standing_0.png)");
    yasuo->addStandingAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_standing_1.png)");
    yasuo->addStandingAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_standing_2.png)");
    yasuo->addStandingAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_standing_3.png)");
    yasuo->addStandingAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_standing_4.png)");
    yasuo->addStandingAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_standing_5.png)");

    yasuo->addWhirlwindAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_stab_0.png)");
    yasuo->addWhirlwindAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_stab_1.png)");
    yasuo->addWhirlwindAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_stab_2.png)");
    yasuo->addWhirlwindAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_stab_3.png)");
    yasuo->addWhirlwindAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_stab_4.png)");

    yasuo->addStabAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_stab_0.png)");
    yasuo->addStabAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_stab_1.png)");
    yasuo->addStabAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_stab_2.png)");
    yasuo->addStabAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_stab_3.png)");
    yasuo->addStabAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_stab_4.png)");
    yasuo->addStabAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_stab_4.png)");
    yasuo->addStabAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_stab_4.png)");
    yasuo->addStabAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_stab_4.png)");
    yasuo->addStabAnimation(R"(C:\Users\pc\CLionProjects\another-test\resources\yasuo_stab_0.png)");

    //yasuo->AddAnimation("C:\\Users\\pc\\CLionProjects\\another-test\\resources\\yasuo_norm_1.png");
    //yasuo->SetHitBox(16, 5, 36, 58);
    //yasuo->SetHitBox(46, 13, 20, 35);
    yasuo->setHitBox(92, 26, 40, 70);
}

void Manager::init(const char *title, int x_pos, int y_pos, int width, int height, bool fullscreen) {
    int is_fullscreen = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    if (!SDL_Init(SDL_INIT_EVERYTHING)) {
        window = SDL_CreateWindow(title, x_pos, y_pos, width, height, is_fullscreen);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }


    initYasuo();

    mp = new Map(20, 16);
    for (int row = 0; row < 16; ++row) {
        for (int column = 0; column < 20; ++column) {
            std::cout << mp->schemeMap[row][column] << " ";
        }
        std::cout << "\n";
    }

    for (int i = 1; i <= 7; ++i) {
        std::string st = R"(C:\Users\pc\CLionProjects\another-test\resources\under-working\loc\frame_)";
        st+=std::to_string(i)+".png";
        char path[st.size()+1];
        strcpy(path, st.c_str());
        yasuo->getSword()->addAnimation(path);
        //exit(0);
    }

    bg = new Entity();
    bg->loadMainTexture(R"(C:\Users\pc\CLionProjects\another-test\resources\background.png)");
    bg->setPosition(0,0);
    bg->setDestR(0,0,1280,720);
}

void Manager::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_a:
                    yasuo->moveLeft();
                    break;
                case SDLK_d:
                    yasuo->moveRight();
                    break;
                case SDLK_j:
                    yasuo->AttackJ();
                default:
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_a:
                    yasuo->stopMovingLeft();
                    break;
                case SDLK_d:
                    yasuo->stopMovingRight();
                    break;
            }
            break;
        default:
            break;
    }
    yasuo->setWillBeBlocked(noOutOfBound() + noCollision() != 2);
}



void Manager::update() {
    yasuo->Update();
    //exit(0);
    yasuo->getSword()->Update();
}

void Manager::render() {
    SDL_RenderClear(renderer);
    bg->Render();
    //mp->drawMap();
    yasuo->Render();
    SDL_RenderPresent(renderer);
}

void Manager::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

bool Manager::running() {
    return is_running;
}
