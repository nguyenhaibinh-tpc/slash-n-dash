//
// Created by pc on 25/1/2021.
//

#ifndef ANOTHER_TEST_TEXTURELOADER_H
#define ANOTHER_TEST_TEXTURELOADER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


class TextureLoader {
public:
    static SDL_Texture *LoadTexture(const char *fileName);
    static void Draw(SDL_Texture *tex,const SDL_Rect &srcR,const SDL_Rect &destR);
};


#endif //ANOTHER_TEST_TEXTURELOADER_H
