//
// Created by Anton on 28-4-2020.
//

#include "Bullet.h"
void Bullet::firePlayer() {
    yPos -= 15;
}
void Bullet::fireEnemy(){
    yPos +=5;
}