//
// Created by malon on 26/05/2020.
//

#include "Bonus.h"
void Bonus::AddBullets(int* kogels) {
    *kogels = *kogels+10;
}
void Bonus::AddTime(int *gameTime) {
    *gameTime = *gameTime+10;
}
void Bonus::DecreasLife(int *PLS_life) {
    *PLS_life = *PLS_life-1;
}