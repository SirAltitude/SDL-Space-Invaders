//
// Created by Anton on 29-4-2020.
//

#ifndef PROGRAMMEREN_SDLENEMYSHIP_H
#define PROGRAMMEREN_SDLENEMYSHIP_H


#include <SDL2/SDL_render.h>
#include "../Abstract/EnemyShip.h"

class SDLEnemyShip: public EnemyShip {
public: SDLEnemyShip(SDL_Renderer* renderer, SDL_Texture* afbeelding);
    void visualize(double scaleX, double scaleY);

private: SDL_Renderer* scherm;
         SDL_Texture* imgES;
         int breedte, hoogte, xP, yP;
};


#endif //PROGRAMMEREN_SDLENEMYSHIP_H
