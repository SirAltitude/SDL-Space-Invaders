//
// Created by Anton on 28-4-2020.
//

#ifndef PROGRAMMEREN_SDLBULLET_H
#define PROGRAMMEREN_SDLBULLET_H


#include <SDL2/SDL_render.h>
#include "../Abstract/Bullet.h"

class SDLBullet: public Bullet {
public:
    SDLBullet(SDL_Renderer* scherm, SDL_Texture* imgB);
    void visualize(double scaleX, double scaleY);

private:
    SDL_Renderer* scherm;
    SDL_Texture* imgBullet;
    int breedte, hoogte, xP, yP;
};


#endif //PROGRAMMEREN_SDLBULLET_H
