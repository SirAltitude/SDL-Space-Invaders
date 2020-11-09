//
// Created by Anton on 28-4-2020.
//

#ifndef PROGRAMMEREN_SDLPLAYERSHIP_H
#define PROGRAMMEREN_SDLPLAYERSHIP_H

#include <SDL2/SDL_render.h>
#include "../Abstract/PlayerShip.h"

class SDLPlayerShip: public PlayerShip {
public: SDLPlayerShip(SDL_Renderer* renderer, SDL_Texture* afbeelding);
        void visualize(double scaleX, double scaleY);

private: SDL_Renderer* scherm;
         SDL_Texture* imgPS;
         int breedte, hoogte, xP, yP;
};


#endif //PROGRAMMEREN_SDLPLAYERSHIP_H
