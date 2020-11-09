//
// Created by malon on 26/05/2020.
//

#ifndef PROGRAMMEREN_BONUS_H
#define PROGRAMMEREN_BONUS_H


#include "Entity.h"

class Bonus: public Entity {
public:
    void AddBullets(int* kogels);
    void AddTime(int* gameTime);
    void DecreasLife(int *PLS_life);

};


#endif //PROGRAMMEREN_BONUS_H
