 //
// Created by Anton on 28-4-2020.
//

#include <iostream>
#include "SDLPlayerShip.h"

using namespace std;
SDLPlayerShip::SDLPlayerShip(SDL_Renderer* renderer, SDL_Texture* afbeelding) {
    scherm = renderer;
    imgPS = afbeelding;
}

void SDLPlayerShip::visualize(double scaleX, double scaleY) {
    xP = this->xPos * scaleX;
    yP = this->yPos * scaleY;
    breedte = this->Breedte * scaleX;
    hoogte = this->Hoogte * scaleY;
    SDL_Rect dstrect = {xP,yP,breedte,hoogte};
    SDL_RenderCopy(scherm,imgPS,NULL,&dstrect);
}
