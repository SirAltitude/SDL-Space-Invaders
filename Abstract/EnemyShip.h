//
// Created by Anton on 29-4-2020.
//

#ifndef PROGRAMMEREN_ENEMYSHIP_H
#define PROGRAMMEREN_ENEMYSHIP_H


#include "Entity.h"

class EnemyShip: public Entity {
public:
    void xMove(int direction);
    void yMove();
};

#endif //PROGRAMMEREN_ENEMYSHIP_H
