//
// Created by Anton on 28-4-2020.
//

#include <SDL2/SDL_events.h>
#include "SDLEvent.h"
SDLEvent::SDLEvent(bool* isLive, SDL_Renderer* renderer) {
    isRunning = isLive;
    scherm = renderer;
}

bool SDLEvent::gameRunning() {
    return *isRunning;
}
int SDLEvent::getXScale() {
    return resizedBreedte;
}
int SDLEvent::getYScale() {
    return resizedHoogte;
}
int SDLEvent::eventManager() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            *isRunning = false;
            break;
        case SDL_WINDOWEVENT:
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                resizedBreedte = event.window.data1;
                resizedHoogte = event.window.data2;
                SDL_RenderPresent(scherm);
                input = 3;
            }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    input = -1;
                    break;
                case SDLK_RIGHT:
                    input = 1;
                    break;
                case SDLK_SPACE:
                    input = 2;
                    break;
                case SDLK_RETURN:
                    input = 4;
                    break;
                case SDLK_p:
                    input = 5;
                    break;
                default:
                    input = 0;
                    break;
            }
            break;
        default:
            input = 0;
            break;
    } return input;
}