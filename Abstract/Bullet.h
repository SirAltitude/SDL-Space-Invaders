//
// Created by Anton on 28-4-2020.
//

#ifndef PROGRAMMEREN_BULLET_H
#define PROGRAMMEREN_BULLET_H


#include "Entity.h"

class Bullet: public Entity {
public:
    void firePlayer();
    void fireEnemy();
};


#endif //PROGRAMMEREN_BULLET_H
