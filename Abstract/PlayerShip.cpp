//
// Created by Anton on 28-4-2020.
//

#include "PlayerShip.h"

void PlayerShip::move(int direction) {
    switch(direction) {
        case 1:
            xPos += 6;
            break;
        case -1:
            xPos -= 6;
            break;
        default:
            break;
    }
}