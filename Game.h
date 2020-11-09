//
// Created by Anton on 28-4-2020.
//

#ifndef PROGRAMMEREN_GAME_H
#define PROGRAMMEREN_GAME_H
#include "Abstract/AbstractFact.h"
#include "Abstract/EnemyShip.h"
#include <list>
#include <string>
#include <sstream>
#include <SDL2/SDL_quit.h>
#include <chrono>
#include "time.h"
#include "math.h"

using namespace std;
using namespace chrono;
class Game {
public: Game(AbstractFact* F);
    void run();
private: AbstractFact* AF;

    const int GAME_breedte = 1080;
    const int GAME_hoogte = 720;
    const int GAME_marge = floor(GAME_breedte/100);

    double xFactor = 1.0;
    double yFactor = 1.0;

    enum keyboardInput{links = -1, rechts = 1, spacebar = 2, escape, resized = 3, started = 4, paused = 5};
    enum bulletDir{up = 1, down = -1};

    bool isDebug = false;
    bool isStarted = false;
    bool isCountedDown = false;
    bool isCompleted = false;
    bool isPaused = false;

    bool isMusicStarted = false;
    bool isCDmusicDone = false;
    int score = 0;
    int expl = 4;

    //SCREEN
    const int SS_b = GAME_breedte-GAME_breedte/2;       //Logo
    const int SS_h = GAME_hoogte - GAME_hoogte/2;
    int SS_x = GAME_breedte/2-SS_b/2;
    int SS_y = GAME_hoogte/2 -SS_h/2;

    const int TXT_b = GAME_breedte-GAME_breedte/2;      //Text
    const int TXT_h = 50;
    int TXT_x = GAME_breedte/2-SS_b/2;
    int TXT_y = GAME_hoogte/2 +TXT_h*2;

    const int cd_b = SS_b/6;                            //Countdown
    const int cd_h = cd_b;
    int cd_x = GAME_breedte/2-cd_b/2;
    int cd_y = GAME_hoogte/2-cd_h/2;

    const int pause_b = TXT_b/2;                        //Pauze
    const int pause_h = TXT_h*2;
    int pause_x = GAME_breedte/2-pause_b/2;
    int pause_y = GAME_hoogte/2-pause_h/2;

    const int ending_b = TXT_b;
    const int ending_h = SS_h/2;
    int ending_x = GAME_breedte/2-ending_b/2;
    int ending_y = GAME_hoogte/2-ending_h/2;

    //PLAYERSHIP
    const int PLS_b = 50;
    const int PLS_h = 60;
    int PLS_x = GAME_breedte/2-PLS_b/2;
    int PLS_y = GAME_hoogte - PLS_h;
    int PLS_life = 3;
    bool isPLayerShipHit = false;

    //ENEMYSHIP
    const int ES_b = PLS_b;
    const int ES_h = PLS_h;
    const int ES_afstand = ES_b/2;
    int aantalES_perLijn = 10;
    int ES_x = (GAME_breedte/2)-((aantalES_perLijn/2)*(ES_b))-(aantalES_perLijn/2-1)*ES_afstand-ES_afstand/2;
    int ES_y = GAME_marge + ES_h;
    int ES_layer = 2;
    const int ES_start_y = ES_y;
    const int ES_start_x = ES_x;
    int ES_layer_x;
    int richting = 1;
    list<EnemyShip*> es_lijst1;
    list<EnemyShip*> es_lijst2;
    list<EnemyShip*> es_lijst3;
    list<EnemyShip*> es_lijst_all;

    list<EnemyShip*>::iterator it;
    EnemyShip* collidedES;
    EnemyShip* explodedES;
    EnemyShip* shotES;
    bool isEnemyShipShot = false;
    bool switchES = false;
    bool isLayerAdded = false;
    bool isLayer2Added = false;
    bool isLayer3Added = false;

    //PS KOGEL
    const int KGL_b = 12;
    const int KGL_h = 60;
    int KGL_x;
    int KGL_y = PLS_y-KGL_h/2;
    bool isShot = false;
    list<Bullet*> kgl_lijst;

    int PLS_ammo = 10;


    //ES KOGEL
    Bullet* esKGL;
    bool isSchipChosen = false;

    //SCORE
    const int score_b = GAME_breedte/10;
    const int score_h = PLS_h/2;
    const int score_x = GAME_marge*2;
    const int score_y = score_x;

    //TIMERS
    clockid_t cdTimer;
    clockid_t gameTimer;
    clockid_t bonusTimer;
    int maxGameTime = 60;
    const int time_b = score_b;
    const int time_h = score_h;
    int time_x = score_x + score_b + score_b/2;
    int time_y = score_y;
    int millisec, millisec2, millisec3 = 0;
    int sec, sec2, sec3 = 0;

    //LIFE
    int hearts = 3;
    const int life_b = time_b/3;
    const int life_h = time_h;
    const int life_x = GAME_breedte-GAME_marge-life_b*3;
    const int life_y = time_y;

    //PowerUP
    const int P_up_b = ES_b*2;
    const int P_up_h = P_up_b;
    bool isBonusAvailable = false;
    int BonusChoice = 0;
    //Bullets
    int Bullets_x = 0;
    int Bullets_y = 0;
    Bonus* addition;
    const int ammo_x = GAME_breedte/2-time_b - score_b;
    const int ammo_y = time_y;
    const int ammo_b = time_b;
    const int ammo_h = time_h;

};


#endif //PROGRAMMEREN_GAME_H
