//
// Created by pc on 31/1/2021.
//

#ifndef ANOTHER_TEST_ENTITY_H
#define ANOTHER_TEST_ENTITY_H

#include "TextureLoader.h"

class Entity {
public:
    //Entity(const char *texture, int xpos, int ypos);
    Entity();

    ~Entity();

    void loadMainTexture(const char *texture);

    void setPosition(int xpos, int ypos);

    void Render();

protected:
    SDL_Texture *objTexture;
    SDL_Rect srcR, destR;
public:
    SDL_Texture *getMainTexture() const;

    void setMainTexture(SDL_Texture *mainTexture);

    const SDL_Rect &getSrcR() const;

    void setSrcR(const SDL_Rect &srcR);

    const SDL_Rect &getDestR() const;

    void setDestR(const SDL_Rect &destR);
};


#endif //ANOTHER_TEST_ENTITY_H
