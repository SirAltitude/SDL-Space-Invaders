//
// Created by Anton on 28-4-2020.
//

#include "SDLBullet.h"
SDLBullet::SDLBullet(SDL_Renderer* renderer, SDL_Texture* afbeelding){
    scherm = renderer;
    imgBullet = afbeelding;
}
void SDLBullet::visualize(double scaleX, double scaleY) {
    xP = this->xPos * scaleX;
    yP = this->yPos * scaleY;
    breedte = this->Breedte * scaleX;
    hoogte = this->Hoogte * scaleY;
    SDL_Rect dstrect = {xP,yP,breedte,hoogte};
    SDL_RenderCopy(scherm,imgBullet,NULL,&dstrect);
}