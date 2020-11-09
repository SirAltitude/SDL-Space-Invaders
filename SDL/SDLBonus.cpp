//
// Created by malon on 26/05/2020.
//

#include "SDLBonus.h"
SDLBonus::SDLBonus(SDL_Renderer* renderer, SDL_Texture* afbeelding){
    scherm = renderer;
    imgBonus = afbeelding;
}
void SDLBonus::visualize(double scaleX, double scaleY) {
    xP = this->xPos * scaleX;
    yP = this->yPos * scaleY;
    breedte = this->Breedte * scaleX;
    hoogte = this->Hoogte * scaleY;
    SDL_Rect dstrect = {xP,yP,breedte,hoogte};
    SDL_RenderCopy(scherm,imgBonus,NULL,&dstrect);
}