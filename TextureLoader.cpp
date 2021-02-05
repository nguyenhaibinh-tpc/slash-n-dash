//
// Created by pc on 25/1/2021.
//

#include "TextureLoader.h"
#include "Manager.h"

SDL_Texture * TextureLoader::LoadTexture(const char *fileName) {
    SDL_Surface *tmp = IMG_Load(fileName);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Manager::renderer, tmp);
    SDL_FreeSurface(tmp);
    return tex;
}

void TextureLoader::Draw(SDL_Texture *tex,const  SDL_Rect &srcR,const  SDL_Rect &destR) {
    SDL_RenderCopy(Manager::renderer, tex, nullptr, &destR);
}

