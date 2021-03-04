//
// Created by pc on 10/2/2021.
//

#ifndef ANOTHER_TEST_BUTTON_H
#define ANOTHER_TEST_BUTTON_H

#include "Entity.h"

class Button : public Entity {
public:
    void handleEvents(SDL_Event event);
    void loadActiveTexture(const char *texture);
    void loadInactiveTexture(const char *texture);
    void Render();
    void setIsActive(bool isActive);
    bool isHasOrder() const;
    void setHasOrder(bool hasOrder);

//private:
    bool isActive;
    bool hasOrder = false;
    Uint32 timeSinceLastOrder;
    SDL_Texture *inActiveTexture, *activeTexture;
};


#endif //ANOTHER_TEST_BUTTON_H
