//
// Created by Anton on 28-4-2020.
//

#include "Entity.h"
#include <iostream>

using namespace std;
void Entity::setX(int xCoordinaat){
    xPos = xCoordinaat;
}

void Entity::setY(int yCoordinaat){
    yPos = yCoordinaat;
}
void Entity::setBreedte(int width) {
    Breedte = width;
}

void Entity::setHoogte(int height) {
    Hoogte = height;
}

void Entity::setData(int x, int y, int b, int h){
    xPos = x;
    yPos = y;
    Breedte = b;
    Hoogte = h;
}
int Entity::getX() {
    return xPos;
}
int Entity::getY() {
    return yPos;
}
int Entity::getH()
{
    return Hoogte;
}
int Entity::getB()
{
    return Breedte;
}
void Entity::printData() {
    cout << "x: " << this->xPos << " y: " << this->yPos << " b: " << this->Breedte << " h: " << this->Hoogte << endl;
}

bool Entity::collision(Entity* object) {

    if((this->yPos <= object->yPos + this->Hoogte/2 && this->yPos >= object->yPos) or (this->yPos <= object->yPos && this->yPos + this->Hoogte/2 >= object->yPos))
    {
        if((this->xPos <= object->xPos && this->xPos + this->Breedte/1.5 >= object->xPos) or (this->xPos <= object->xPos + object->Breedte/1.5 && this->xPos >= object->xPos))
        {
           collided = true;
        }
        else collided = false;
    }
    return  collided;
}