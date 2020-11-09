//
// Created by Anton on 28-4-2020.
//

#ifndef PROGRAMMEREN_SDLFACT_H
#define PROGRAMMEREN_SDLFACT_H


#include <SDL2/SDL_ttf.h>
#include "../Abstract/AbstractFact.h"
#include "SDL2/SDL.h"
#include "../Abstract/Bonus.h"
#include "SDL2/SDL_mixer.h"

class SDLFact: public AbstractFact {
public: SDLFact();
    PlayerShip* createPlayerShip();
    EnemyShip* createEnemyShip();
    Event* createEventManager();
    Bullet* fireBullet(int dir);
    Bonus* createAddition(int choice);
    void update();
    void background();
    void start(int x, int y, int b, int h, double scaleX, double scaleY);
    void startText(int x, int y, int b, int h, double scaleX, double scaleY);
    void countdown(int t, int x, int y, int h, int b, double scaleX, double scaleY);
    void score(int score, int x, int y, int b, int h, double scaleX, double scaleY);
    void explode(int count, int x, int y, int b, int h, double scaleX, double scaleY);
    void pause(int x, int y, int b, int h, double scaleX, double scaleY);
    void end(int choice, int x, int y, int b, int h, double scaleX, double scaleY);
    void timer(int c, int x, int y, int b, int h, double scaleX, double scaleY);
    void life(int c, int x, int y, int b, int h, double scaleX, double scaleY);
    void bulletamount(int c, int x, int y, int b, int h, double scaleX, double scaleY);
    void IntroMusic();
    void BackGroundMusic();
    void CountDownMusic();
    void PauseTunes();

private:
    int DISPLAY_Breedte = 1080;
    int DISPLAY_Hoogte = 720;
    SDL_Renderer* scherm;
    SDL_Texture* imgPS;
    SDL_Texture* imgBG;
    SDL_Texture* imgKGL_PL;
    SDL_Texture* imgKGL_ES;
    SDL_Texture* imgES;
    SDL_Texture* imgSS;
    SDL_Texture* expl1;
    SDL_Texture* expl2;
    SDL_Texture* expl3;
    SDL_Texture* expl4;
    SDL_Texture* life_heart;
    SDL_Texture* powerUPbullets;
    SDL_Texture* powerUPtime;
    SDL_Texture* powerDOWNlife;

    Mix_Music* backgroundMusic;
    Mix_Music* introMusic;
    Mix_Music* cdMusic;
    Mix_Chunk* KogelSchot;
    Mix_Chunk* BulletHit;
    Mix_Chunk* loser;
    Mix_Chunk* winner;
    Mix_Chunk* bonus;

    bool isExplodedPlayed = false;
    bool isBonusPlayed = false;
    bool run = false;

    //Tekst data
    TTF_Font* ltrtype;
};


#endif //PROGRAMMEREN_SDLFACT_H
