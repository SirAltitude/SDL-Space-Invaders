//
// Created by malon on 26/05/2020.
//

#ifndef PROGRAMMEREN_SDLBONUS_H
#define PROGRAMMEREN_SDLBONUS_H


#include <SDL2/SDL_render.h>
#include "../Abstract/Bonus.h"

class SDLBonus: public Bonus {
public:
    SDLBonus(SDL_Renderer* scherm, SDL_Texture* imgB);
    void visualize(double scaleX, double scaleY);

private:
    SDL_Renderer* scherm;
    SDL_Texture* imgBonus;
    int breedte, hoogte, xP, yP;
};

#endif //PROGRAMMEREN_SDLBONUS_H
