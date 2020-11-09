//
// Created by Anton on 28-4-2020.
//

#ifndef PROGRAMMEREN_ABSTRACTFACT_H
#define PROGRAMMEREN_ABSTRACTFACT_H

#include "PlayerShip.h"
#include "Event.h"
#include "Bullet.h"
#include "EnemyShip.h"
#include "Bonus.h"

class AbstractFact{
public:
    virtual PlayerShip* createPlayerShip() = 0;
    virtual EnemyShip* createEnemyShip()=0;
    virtual Event* createEventManager() = 0;
    virtual Bullet* fireBullet(int dir) = 0;
    virtual Bonus* createAddition(int choice) = 0;

    virtual void update()=0;
    virtual void background()=0;
    virtual void start(int x, int y, int b, int h, double scaleX, double scaleY)=0;
    virtual void startText(int x, int y, int b, int h, double scaleX, double scaleY) = 0;
    virtual void countdown(int t, int x, int y, int h, int b, double scaleX, double scaleY)=0;
    virtual void score(int score, int x, int y, int b, int h, double scaleX, double scaleY)=0;
    virtual void explode(int count, int x, int y, int b, int h, double scaleX, double scaleY)=0;
    virtual void pause(int x, int y, int b, int h, double scaleX, double scaleY)=0;
    virtual void end(int choice, int x, int y, int b, int h, double scaleX, double scaleY)=0;
    virtual void timer(int c, int x, int y, int b, int h, double scaleX, double scaleY)=0;
    virtual void life(int c, int x, int y, int b, int h, double scaleX, double scaleY)=0;
    virtual void bulletamount(int c, int x, int y, int b, int h, double scaleX, double scaleY)=0;
    virtual void IntroMusic()=0;
    virtual void BackGroundMusic()=0;
    virtual void PauseTunes()=0;
    virtual void CountDownMusic()=0;
};


#endif //PROGRAMMEREN_ABSTRACTFACT_H
