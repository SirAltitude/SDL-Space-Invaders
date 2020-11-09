//
// Created by Anton on 29-4-2020.
//

#include "SDLEnemyShip.h"
SDLEnemyShip::SDLEnemyShip(SDL_Renderer* renderer, SDL_Texture* afbeelding) {
    scherm = renderer;
    imgES = afbeelding;
}

void SDLEnemyShip::visualize(double scaleX, double scaleY) {
    xP = this->xPos * scaleX;
    yP = this->yPos * scaleY;
    breedte = this->Breedte * scaleX;
    hoogte = this->Hoogte * scaleY;
    SDL_Rect dstrect = {xP,yP,breedte,hoogte};
    SDL_RenderCopy(scherm,imgES,NULL,&dstrect);
}