//
// Created by pc on 31/1/2021.
//

#include "Entity.h"
#include "Manager.h"

Entity::Entity() {

}
Entity::~Entity() {

}

void Entity::loadMainTexture(const char *texture) {
    objTexture = TextureLoader::LoadTexture(texture);
}

void Entity::setPosition(int xpos, int ypos) {
    destR.x = xpos;
    destR.y = ypos;
    srcR.h = srcR.w = 1000;
    srcR.x = srcR.y = 0;
    destR.h = 104;
    destR.w = 228;
}


void Entity::Render() {
    //SDL_RenderCopy(objRenderer, objTexture, &srcR, &destR);
    SDL_RenderCopy(Manager::renderer, objTexture, nullptr, &destR);
}

