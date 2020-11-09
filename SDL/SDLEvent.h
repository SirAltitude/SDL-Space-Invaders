//
// Created by Anton on 28-4-2020.
//

#ifndef PROGRAMMEREN_SDLEVENT_H
#define PROGRAMMEREN_SDLEVENT_H


#include <SDL2/SDL_render.h>
#include "../Abstract/Event.h"

class SDLEvent: public Event {
public:
    SDLEvent(bool* isLive, SDL_Renderer* renderer);
    bool gameRunning();
    int eventManager();
    int getXScale();
    int getYScale();
    int input;
private:
    SDL_Renderer* scherm;
};


#endif //PROGRAMMEREN_SDLEVENT_H
