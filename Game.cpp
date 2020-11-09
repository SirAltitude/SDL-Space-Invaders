//
// Created by Anton on 28-4-2020.
//

#include "Game.h"
#include "math.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
Game::Game(AbstractFact *F) {
    AF = F;
}

void Game::run() {

    //Debug
    if(isDebug)
    {
        isStarted = true;
        isCountedDown = true;
        cout << "LET OP: isStarted en isCountedDown staan op true!" << endl;
    }

    //Timer starten
    clockid_t Current_Time, Game_started = clock();

    //Gebeurtenissen
    Event *event = AF->createEventManager();

    //Objecten
    PlayerShip *ps = AF->createPlayerShip();                                //Speler schip
    ps->setData(PLS_x, PLS_y, PLS_b, PLS_h);


    for (int i = 0; i < aantalES_perLijn; i++) {                            //Lijst met enemy schepen
        EnemyShip *es = AF->createEnemyShip();
        es->setData(ES_x + i * (ES_afstand + ES_b), ES_y, ES_b, ES_h);   //enkel de x positie verandert
        es_lijst1.push_back(es);
    }
    copy(es_lijst1.rbegin(),es_lijst1.rend(),front_inserter(es_lijst_all)); //de eerste laag wordt in de algemene lijst geduwd
    //GAME LOOP
    while (event->gameRunning() and !isCompleted) {
        AF->background();                                  //Achtergrond altijd eerst inladen zodat hierop verder kan gebouw worden
        Current_Time = clock();
        millisec = Current_Time - Game_started;
        sec = millisec / (CLOCKS_PER_SEC);

        switch (event->eventManager()) {
            case resized:
                xFactor = double(event->getXScale()) / GAME_breedte;
                yFactor = double(event->getYScale()) / GAME_hoogte;
                break;
            case links:
                if (ps->getX() >= GAME_marge)
                    ps->move(links);
                break;
            case rechts:
                if (ps->getX() <= GAME_breedte - GAME_marge)
                    ps->move(rechts);
                break;
            case spacebar:
                if (!isShot and PLS_ammo > 0 and isStarted) {            //bool isStarted wordt enkel op true gezet als men hiervoor op enter heeft geduwd
                    Bullet *kgl = AF->fireBullet(up);
                    KGL_x = ps->getX() + PLS_b / 2 -KGL_b / 2; //de kogel neemt de x positie van de speler zijn schip op moment van het schieten
                    kgl->setData(KGL_x, KGL_y, KGL_b, KGL_h);
                    kgl_lijst.push_back(kgl);
                    isShot = true;
                    PLS_ammo -= 1;
                }
                break;
            case started:
                isStarted = true;
                cdTimer = clock();
                AF->PauseTunes();
                isMusicStarted = false;
                break;
            case paused:
                isPaused = !isPaused;
                break;
            default:
                break;
        }

        //Intro scherm
        if (!isStarted and sec < 2) {      //na twee seconden wachten beweegt het logo omhoog
            AF->start(SS_x, SS_y, SS_b, SS_h, xFactor, yFactor);
            AF->update();
            if(!isMusicStarted){
                AF->IntroMusic();
                isMusicStarted = true;
            }
        } else if (!isStarted and sec >= 2) {
            if (SS_y > GAME_breedte / 50) {
                SS_y -= 2;
            } else {          //vervolgens komt er een boodschap bij dat men op enter moet duwen
                if (sec >= 4 and sec % 2 == 0)
                    AF->startText(TXT_x, TXT_y, TXT_b, TXT_h, xFactor, yFactor);
            }
            AF->start(SS_x, SS_y, SS_b, SS_h, xFactor, yFactor);
            AF->update();
//            AF->PauseTunes();
//            isMusicStarted = false;
        } else {

            if (!isCountedDown) {       //aftelling tot 3 vooraleer het spel begint
                if(!isCDmusicDone){
                    AF->CountDownMusic();
                    isCDmusicDone = true;
                }

                Current_Time = clock();
                millisec = Current_Time - cdTimer;
                sec = millisec / (CLOCKS_PER_SEC);
                if (sec <= 2) //2 omdat de timer van nul begint
                {
                    AF->countdown(sec + 1, cd_x, cd_y, cd_b, cd_h, xFactor, yFactor);
                    AF->update();
                } else {
                    isCountedDown = true;
                    isMusicStarted = false;
                    cdTimer = clock();
                    gameTimer = clock();
                }
            } else {
                if (isPaused) {
                    AF->pause(pause_x, pause_y, pause_b, pause_h, xFactor, yFactor);
                    AF->update();
                } else {
                    //Spel bezig
                    if(!isMusicStarted){
                        AF->BackGroundMusic();
                        isMusicStarted = true;
                    }


                    //Beweging EnemyShips
                    // Enemyships bewegen constant op de x-as, afhankelijk van de richting naar links of rechts.
                    // ze bewegen enkel omlaag als de meest buitenste enemyship de zijkant van het scherm raakt.
                    enum {vliegLinks = -1, vliegRechts = 1};
                    if(richting == vliegRechts)
                    {
                        for(EnemyShip* schip: es_lijst_all)
                        {
                            if(schip->getX() >= GAME_breedte-ES_b-GAME_marge) {
                                switchES = true;
                                richting = vliegLinks;
                            }
                        }
                    }
                    else if(richting == vliegLinks)
                    {
                        for(EnemyShip* schip: es_lijst_all)
                        {
                            if(schip->getX() <= GAME_marge)
                            {
                                switchES = true;
                                richting = vliegRechts;
                            }
                        }
                    }
                    if(switchES)
                    {
                        for(EnemyShip* schip: es_lijst_all)
                        {
                            schip->yMove();
                        }
                    }
                    for(EnemyShip* schip: es_lijst_all)
                    {
                        schip->xMove(richting);
                    }
                    // In deze switch wordt afhankelijk van de reeds gespawnede laag ES (in het begin = 1) een nieuwe gespawnd;
                    switch(ES_layer) {
                        case 2:
                            for (EnemyShip *schip: es_lijst1) {
                                if (schip->getY() >= ES_start_y + ES_h + ES_afstand && es_lijst_all.front()->getX() >= ES_start_x && !isLayer2Added) {
//                                    copy(es_lijst2.rbegin(), es_lijst2.rend(), front_inserter(es_lijst_all));
                                    ES_layer = 3;
                                    isLayer2Added = true;
                                    ES_layer_x = es_lijst_all.front()->getX();
                                }
                            }
                            break;
                        case 3:
                            for (EnemyShip *schip: es_lijst2) {
                                if (schip->getY() >= ES_start_y + ES_h + ES_afstand && es_lijst_all.front()->getX() >= ES_start_x && !isLayer3Added) {
//                                    copy(es_lijst3.rbegin(), es_lijst3.rend(), front_inserter(es_lijst_all));
                                    ES_layer =4;
                                    isLayer3Added = true;
                                    ES_layer_x = es_lijst_all.front()->getX();
                                }
                            }
                            break;
                        default:
                            break;
                    }
                    if(isLayer2Added)
                    {
                        for (int i = 0; i < aantalES_perLijn; i++) {                            //Lijst met enemy schepen
                            EnemyShip *es = AF->createEnemyShip();
                            es->setData(ES_layer_x + i * (ES_afstand + ES_b), ES_y, ES_b, ES_h);   //enkel de x positie verandert
                            es_lijst2.push_back(es);
                        }
                        copy(es_lijst2.rbegin(), es_lijst2.rend(), front_inserter(es_lijst_all));
                        isLayer2Added = false;
                    }
                    if(isLayer3Added)
                    {
                        for (int i = 0; i < aantalES_perLijn; i++) {                            //Lijst met enemy schepen
                            EnemyShip *es = AF->createEnemyShip();
                            es->setData(ES_layer_x + i * (ES_afstand + ES_b), ES_y, ES_b, ES_h);   //enkel de x positie verandert
                            es_lijst3.push_back(es);
                        }
                        copy(es_lijst3.rbegin(), es_lijst3.rend(), front_inserter(es_lijst_all));
                        isLayer3Added = false;
                    }


                    Current_Time = clock();
                    millisec2 = Current_Time - gameTimer;
                    sec2 = millisec2 / (CLOCKS_PER_SEC);
                    int i = rand()%aantalES_perLijn+1;      //een random getal van 1 tot het aantal schepen er zijn per lijn
                    if(sec2%4==0 and !isSchipChosen)        //om de vier seconden schiet er een vijand
                    {
                        int j = 1;
                        for(EnemyShip* schip: es_lijst_all) {       //omdat list geen methode heeft om 'door te spoelen' naar een bepaalde positie
                            if (j == i and !isSchipChosen) {    //gebruik ik een homemade iterator, waarbij het schip in een tijdelijke variabele gestoken wordt
                                shotES = schip;
                                isSchipChosen = true;
                            } else j++;
                        }
                        isPLayerShipHit = false;
                        esKGL = AF->fireBullet(down);
                        esKGL->setData(shotES->getX()+ES_b/2-KGL_b/2, shotES->getY()+ES_h-KGL_h/2,KGL_b,KGL_h); //data van het gekozen schio (adhv de random waarde)
                    }   //de kogel moet in het midden van het enemyship spawnen dus daarom - breedte/2

                    //Bonussen
                    enum BonusCase{ExtraAmmo = 0, ExtraTime = 1, LessLife = 2};
                    if(sec2%10 == 0 and !isBonusAvailable and maxGameTime-sec2 <= maxGameTime-10) //eerste bonus komt na 10 sec en dan telkens om de 10 sec
                    {
                        Bullets_x = rand()%(GAME_breedte-4*GAME_marge); //random x & y waardes afhankelijk van de afmetingen van het scherm
                        Bullets_y = rand()%(GAME_hoogte-4*GAME_marge);
                        // cout << "X: " << Bullets_x << " Y: " << Bullets_y << endl;
                        isBonusAvailable = true;
                        bonusTimer = clock();
                        BonusChoice = rand()%3;
                        cout << "The randomized bonus was: " << BonusChoice << endl;
                        addition = AF->createAddition(BonusChoice);
                        addition->setData(Bullets_x,Bullets_y,P_up_b,P_up_h);
                    }

                    Current_Time = clock();
                    millisec3 = Current_Time - bonusTimer;
                    sec3 = millisec3/(CLOCKS_PER_SEC);
                    if(sec3 >= 5)       // na 5 seconden wordt de bonus weggehaald
                        isBonusAvailable = false;


                    //Kogel collision
                    for (Bullet *kgl: kgl_lijst) {              //voor elke kogel uit de lijst (eigenlijk dus maar één)
                        for (EnemyShip *schip: es_lijst_all) {      //wordt er nagekeken of hij een schip heeft geraakt
                            if (kgl->collision(schip) and !isEnemyShipShot) {
                                collidedES = schip;
                                explodedES = schip;
                                cdTimer = clock();
                                kgl_lijst.remove(kgl);          //de kogel wordt uit de lijst gehaald en zo kan men weer schieten
                                isShot = false;
                                isEnemyShipShot = true;
                            }
                        }
                        if(isBonusAvailable) {
                            if (kgl->collision(addition)) {         //als de bonus wordt geraakt
                                switch (BonusChoice) {
                                    case ExtraAmmo:
                                        addition->AddBullets(&PLS_ammo);     //worden er kogels toegevoegd
                                        break;
                                    case ExtraTime:
                                        addition->AddTime(&(maxGameTime));
                                        break;
                                    case LessLife:
                                        addition->DecreasLife(&hearts);
                                        break;
                                    default:break;
                                }
                                // cout << PLS_ammo << endl;
                                kgl_lijst.remove(kgl);          //de kogel wordt uit de lijst gehaald en zo kan men weer schieten
                                isShot = false;
                                isBonusAvailable = false;
                            }
                        }
                    }
                    //Kogel ES collision met PLS
                    if(esKGL->collision(ps) and !isPLayerShipHit)
                    {
                        hearts -= 1;
                        isPLayerShipHit = true;
                        isSchipChosen = false;
                        cout << "Speler heeft nog " <<  hearts << " levens over." << endl;
                    }

                    //Ontploffing animatie enemyschip
                    millisec = Current_Time - cdTimer;
                    if(isEnemyShipShot) {
                        es_lijst_all.remove(collidedES);
                        score += 20;
                        if (millisec <= 75) {
                            AF->explode(expl, explodedES->getX(), explodedES->getY(), explodedES->getB(),explodedES->getH(), xFactor, yFactor);
                        } else if (millisec > 75 and millisec <= 150) {
                            AF->explode(expl - 1, explodedES->getX(), explodedES->getY(), explodedES->getB(),explodedES->getH(), xFactor, yFactor);
                        } else if (millisec > 150 and millisec <= 225) {
                            AF->explode(expl - 2, explodedES->getX(), explodedES->getY(), explodedES->getB(),explodedES->getH(), xFactor, yFactor);
                        } else if (millisec > 225 and millisec <= 300) {
                            AF->explode(expl - 3, explodedES->getX(), explodedES->getY(), explodedES->getB(),explodedES->getH(), xFactor, yFactor);
                            isEnemyShipShot  = false;
                        }
                    }




                    switchES = false;
                    isLayerAdded = false;

                    //Visualisatie
                    ps->visualize(xFactor, yFactor);
                    for (EnemyShip *schip: es_lijst_all) {
                        schip->visualize(xFactor, yFactor);
                    }
                    for (Bullet *kgl: kgl_lijst) {
                        if (kgl->getY() <=0) {     //als een kogel 'out of bounds' gaat, wordt deze uit de lijst gehaald
                            kgl_lijst.remove(kgl);  //zodat men weer kan schieten
                            isShot = false;
                        }
                        kgl->firePlayer();
                        kgl->visualize(xFactor, yFactor);
                    }
                    if(isSchipChosen) {
                        esKGL->fireEnemy();
                        esKGL->visualize(xFactor, yFactor);
                    }
                    if(esKGL->getY() >= GAME_hoogte) {  //als de kogel welke is geschoten door de vijand 'out of bounds'
                        isSchipChosen = false;         //mag er een nieuwe geschoten worden
                    }
                    AF->score(score, score_x, score_y, score_b, score_h, xFactor, yFactor);
                    AF->timer(maxGameTime-sec2, time_x, time_y,time_b,time_h,xFactor,yFactor);
                    AF->life(hearts,life_x,life_y,life_b,life_h,xFactor,yFactor);
                    if(isBonusAvailable)
                    {
                        addition->visualize(xFactor,yFactor);
                    }
                    AF->bulletamount(PLS_ammo,ammo_x,ammo_y,ammo_b,ammo_h,xFactor,yFactor);
                    AF->update();

                    // Afhankelijk van of er gewonnen of verloren is wordt er een respectievelijk positief of negatief eindscherm getoond
                    enum endingChoice{positive = 1, negative = -1};
                    if(es_lijst_all.empty())
                    {
                        isCompleted = true;
                        AF->background();
                        AF->PauseTunes();
                        AF->end(positive,ending_x,ending_y,ending_b,ending_h, xFactor,yFactor);
                        cout << "You won because you shot all enemies!" << endl;
                    }
                    if(hearts == 0)
                    {
                        isCompleted = true;
                        AF->background();
                        AF->PauseTunes();
                        AF->end(negative,ending_x,ending_y,ending_b,ending_h, xFactor,yFactor);
                        cout << "You lost because you have no lives left..." << endl;
                    }
                    if(PLS_ammo == 0 and !isShot)
                    {
                        isCompleted = true;
                        AF->background();
                        AF->PauseTunes();
                        AF->end(negative,ending_x,ending_y,ending_b,ending_h, xFactor,yFactor);
                        cout << "You lost because you have no ammo left..." << endl;
                    }
                    if(maxGameTime-sec2==0)
                    {
                        isCompleted = true;
                        AF->background();
                        AF->PauseTunes();
                        AF->end(negative,ending_x,ending_y,ending_b,ending_h, xFactor,yFactor);
                        cout << "You lost because you ran out of time..." << endl;
                    }
                    if(es_lijst_all.back()->getY()+ES_h >= PLS_y)
                    {
                        isCompleted = true;
                        AF->background();
                        AF->PauseTunes();
                        AF->end(negative,ending_x,ending_y,ending_b,ending_h, xFactor,yFactor);
                        cout << "You lost because you didn't shoot the enemies.." << endl;
                    }

                }
            }
        }
    }
}