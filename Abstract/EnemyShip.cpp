//
// Created by Anton on 29-4-2020.
//

#include "EnemyShip.h"
void EnemyShip::xMove(int direction) {
    switch(direction) {
        case 1:
            xPos += 2;
            break;
        case -1:
            xPos -= 2;
            break;
        default:
            break;
    }
}

void EnemyShip::yMove() {
    yPos += 25;
}
