//
// Created by pc on 10/2/2021.
//

#include "Button.h"
#include "Manager.h"

void Button::loadActiveTexture(const char *texture) {
    activeTexture = TextureLoader::LoadTexture(texture);
}

void Button::loadInactiveTexture(const char *texture) {
    inActiveTexture = TextureLoader::LoadTexture(texture);
}

void Button::Render() {
    SDL_RenderCopy(Manager::renderer, isActive ? activeTexture : inActiveTexture, nullptr, &destR);
}

void Button::handleEvents(SDL_Event event) {
    hasOrder = false;
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            int xpos, ypos;
            SDL_GetMouseState(&xpos, &ypos);
            if (destR.x <= xpos && xpos <= destR.x + destR.w &&
                destR.y <= ypos && ypos <= destR.y + destR.h) {
                if (isActive)
                    hasOrder = true;
            }
            break;
        default:
            break;
    }
}

void Button::setIsActive(bool isActive) {
    Button::isActive = isActive;
}

bool Button::isHasOrder() const {
    return hasOrder;
}

void Button::setHasOrder(bool hasOrder) {
    Button::hasOrder = hasOrder;
}
