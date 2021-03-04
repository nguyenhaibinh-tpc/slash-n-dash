//
// Created by pc on 25/1/2021.
//

#ifndef ANOTHER_TEST_TEXTURELOADER_H
#define ANOTHER_TEST_TEXTURELOADER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL_ttf.h"


class TextureLoader {
public:
    TextureLoader();

    static SDL_Texture *LoadTexture(const char *fileName);

    static void Draw(SDL_Texture *tex, const SDL_Rect &srcR, const SDL_Rect &destR);

    static SDL_Texture *loadNumber(int number, SDL_Rect &rect, int size);

    static SDL_Texture *loadText(const char *text, SDL_Rect &rect);
};


#endif //ANOTHER_TEST_TEXTURELOADER_H
