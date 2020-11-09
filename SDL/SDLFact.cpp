//
// Created by Anton on 28-4-2020.
//

#include "SDLFact.h"
#include <SDL2/SDL_image.h>
#include "SDLPlayerShip.h"
#include "SDLEvent.h"
#include "SDLBullet.h"
#include "SDLEnemyShip.h"
#include "string"
#include "SDLBonus.h"
#include "SDL2/SDL_mixer.h"

#include "iostream"

using namespace std;
SDLFact::SDLFact() {
    //Window aanmaken
    SDL_Window* window = SDL_CreateWindow("2D Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DISPLAY_Breedte,DISPLAY_Hoogte, SDL_WINDOW_RESIZABLE);

    //Renderer aanmaken
    scherm = SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC);

    //Inladen foto's
    SDL_Surface* PS_surface = IMG_Load("../Images/playership.png");     //PlayerShip
    imgPS = SDL_CreateTextureFromSurface(scherm,PS_surface);
    SDL_Surface* BG_surface = SDL_LoadBMP("../Images/background.bmp");  //Achtergrond
    imgBG = SDL_CreateTextureFromSurface(scherm,BG_surface);
    SDL_Surface* KGL_surface = IMG_Load("../Images/bullet_up.png");        //Kogel Speler
    imgKGL_PL= SDL_CreateTextureFromSurface(scherm,KGL_surface);
    SDL_Surface* KGL_ES_surface = IMG_Load("../Images/bullet_down.png");   //Kogel Enemy
    imgKGL_ES = SDL_CreateTextureFromSurface(scherm,KGL_ES_surface);
    SDL_Surface* ES_surface = IMG_Load("../Images/enemyship.png");    //EnemyShip
    imgES = SDL_CreateTextureFromSurface(scherm,ES_surface);
    SDL_Surface* START_SCREEN_surface = IMG_Load("../Images/startscreen.png");  //Start Scherm
    imgSS = SDL_CreateTextureFromSurface(scherm,START_SCREEN_surface);
    SDL_Surface* expl = IMG_Load("../Images/Explosion/1.png");  //animatie voor het ontploffen
    expl1 = SDL_CreateTextureFromSurface(scherm,expl);
    expl = IMG_Load("../Images/Explosion/2.png");
    expl2 = SDL_CreateTextureFromSurface(scherm,expl);
    expl = IMG_Load("../Images/Explosion/3.png");
    expl3 = SDL_CreateTextureFromSurface(scherm,expl);
    expl = IMG_Load("../Images/Explosion/4.png");
    expl4 = SDL_CreateTextureFromSurface(scherm,expl);
    SDL_Surface* LIFE_surface = IMG_Load("../Images/heart.png");        //Speler levens
    life_heart = SDL_CreateTextureFromSurface(scherm,LIFE_surface);
    //Bonus Images
    SDL_Surface* bonus_surface = IMG_Load("../Images/PowerUPbullets.png");  //Extra Kogels
    powerUPbullets = SDL_CreateTextureFromSurface(scherm,bonus_surface);
    bonus_surface = IMG_Load("../Images/PowerUPtime.png");                  //Extra tijd
    powerUPtime = SDL_CreateTextureFromSurface(scherm,bonus_surface);
    bonus_surface = IMG_Load("../Images/PowerDOWNlife.png");                //Minder levens
    powerDOWNlife = SDL_CreateTextureFromSurface(scherm,bonus_surface);

    SDL_Surface* ICON_surface = IMG_Load("../Images/icon.png");
    SDL_SetWindowIcon(window,ICON_surface);

    SDL_FreeSurface(PS_surface);
    SDL_FreeSurface(BG_surface);
    SDL_FreeSurface(KGL_surface);
    SDL_FreeSurface(ES_surface);
    SDL_FreeSurface(START_SCREEN_surface);
    SDL_FreeSurface(expl);
    SDL_FreeSurface(bonus_surface);
    SDL_FreeSurface(ICON_surface);

    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    introMusic = Mix_LoadMUS("../Audio/intro_screen.wav");
    backgroundMusic = Mix_LoadMUS("../Audio/backgroundmusic.mp3");
    KogelSchot = Mix_LoadWAV("../Audio/bullet_shot.wav");
    BulletHit = Mix_LoadWAV("../Audio/explosion.wav");
    cdMusic = Mix_LoadMUS("../Audio/countdown.wav");
    loser = Mix_LoadWAV("../Audio/loser.wav");
    winner = Mix_LoadWAV("../Audio/winner.wav");
    bonus = Mix_LoadWAV("../Audio/bonus.wav");

    TTF_Init();
    ltrtype = TTF_OpenFont("../Font/Lato-Medium.ttf", 50);
    if(ltrtype!=NULL and backgroundMusic!= NULL) {
        run = true;
    }
}
void SDLFact::IntroMusic() {
    Mix_PlayMusic(introMusic, -1);
}
void SDLFact::BackGroundMusic() {
    Mix_PlayMusic(backgroundMusic,-1);
}
void SDLFact::CountDownMusic() {
    Mix_PlayMusic(cdMusic,0);
}
void SDLFact::PauseTunes(){
    Mix_HaltMusic();
}
PlayerShip* SDLFact::createPlayerShip() {
    return new SDLPlayerShip(this->scherm,this->imgPS);
}
EnemyShip* SDLFact::createEnemyShip() {
    return new SDLEnemyShip(this->scherm, this->imgES);
}
Event* SDLFact::createEventManager() {
    return new SDLEvent(&run,this->scherm);
}
Bullet* SDLFact::fireBullet(int dir) {
    Mix_PlayChannel(-1,KogelSchot,0);
    SDL_Texture* afbeelding;
    switch(dir)
    {
        case 1:
            afbeelding = this->imgKGL_PL;
            break;
        case -1:
            afbeelding = this->imgKGL_ES;
            break;
        default:
            break;
    }
    return new SDLBullet(this->scherm,afbeelding);
}
Bonus* SDLFact::createAddition(int choice) {
    if(!isBonusPlayed)
    {
        Mix_PlayChannel(-1,bonus,0);
        isBonusPlayed = true;
    }
    switch (choice) {
    case 0:
        isBonusPlayed = false;
        return new SDLBonus(this->scherm, this->powerUPbullets);
        break;
    case 1:
        isBonusPlayed = false;
        return new SDLBonus(this->scherm, this->powerUPtime);
        break;
    case 2:
        isBonusPlayed = false;
        return new SDLBonus(this->scherm,this->powerDOWNlife);
        break;
    default: return 0;
    }
}

void SDLFact::background()
{
    SDL_RenderClear(this->scherm);
    SDL_RenderCopy(this->scherm,this->imgBG,NULL,NULL);
}
void SDLFact::update()
{
    SDL_RenderPresent(this->scherm);
}

void SDLFact::start(int x, int y, int b, int h, double scaleX, double scaleY) {
    int xP = x*scaleX;
    int yP = y*scaleY;
    int B = b*scaleX;
    int H = h*scaleY;
    SDL_Rect dstrect = {xP, yP, B, H};
    SDL_RenderCopy(this->scherm,this->imgSS, NULL, &dstrect);
}
void SDLFact::startText(int x, int y, int b, int h, double scaleX, double scaleY)
{
    string txt = "Press 'enter' to begin!";
    const char* startText = txt.c_str();
    SDL_Color kleur = {255,255,0};
    SDL_Surface* TXT_surface = TTF_RenderText_Solid(ltrtype,startText,kleur);
    SDL_Texture* TXT_texture = SDL_CreateTextureFromSurface(this->scherm, TXT_surface);

    SDL_FreeSurface(TXT_surface);
    int xP = x*scaleX;
    int yP = y*scaleY;
    int B = b*scaleX;
    int H = h*scaleY;
    SDL_Rect dstrect = {xP, yP, B, H};
    SDL_RenderCopy(this->scherm,TXT_texture, NULL, &dstrect);
}

void SDLFact::countdown(int t, int x, int y, int b, int h, double scaleX, double scaleY)
{
    string txt = to_string(t);
    const char* countdownText = txt.c_str();
    SDL_Color kleur;
    switch(t)
    {
        case 1:
            kleur = {0,255,0};
            break;
        case 2:
            kleur = {255,255,0};
            break;
        case 3:
            kleur = {255,0,0};
            break;
        default:
            break;
    }
    SDL_Surface* cd_surface = TTF_RenderText_Solid(ltrtype,countdownText,kleur);
    SDL_Texture* cd_texture = SDL_CreateTextureFromSurface(this->scherm,cd_surface);

    SDL_FreeSurface(cd_surface);
    int xP = x*scaleX;
    int yP = y*scaleY;
    int B = b*scaleX;
    int H = h*scaleY;
    SDL_Rect dstrect = {xP, yP, B, H};
    SDL_RenderCopy(this->scherm,cd_texture, NULL, &dstrect);
}

void SDLFact::score(int score, int x, int y, int b, int h, double scaleX, double scaleY){
    string tekst = "Score: " + to_string(score);
    const char* txt = tekst.c_str();
    SDL_Color kleur;
    if(score==0)
        kleur = {255,0,0};
    else kleur = {255,255,255};
    SDL_Surface* st = TTF_RenderText_Solid(ltrtype,txt,kleur);
    SDL_Texture* tt = SDL_CreateTextureFromSurface(this->scherm,st);

    SDL_FreeSurface(st);

    int xP = x*scaleX;
    int yP = y*scaleY;
    int B = b*scaleX;
    int H = h*scaleY;

    SDL_Rect dstrect = {xP, yP, B, H};
    SDL_RenderCopy(this->scherm,tt, NULL, &dstrect);
}

void SDLFact::explode(int count, int x, int y, int b, int h, double scaleX, double scaleY)
{
    if(!isExplodedPlayed) {
        Mix_PlayChannel(-1, BulletHit, 0);
        isExplodedPlayed = true;
    }

    int xP = x*scaleX;
    int yP = y*scaleY;
    int B = b*scaleX;
    int H = h*scaleY;
    SDL_Texture* explosion;
    switch (count) {
        case 1:
            explosion = expl1;
            break;
        case 2:
            explosion = expl2;
            break;
        case 3:
            explosion = expl3;
            break;
        case 4:
            explosion = expl4;
            isExplodedPlayed = false;
            break;
        default: break;
    }
    SDL_Rect dstrect = {xP, yP, B, H};
    SDL_RenderCopy(this->scherm,explosion, NULL, &dstrect);
}

void SDLFact::pause(int x, int y, int b, int h, double scaleX, double scaleY) {
    int xP = x*scaleX;
    int yP = y*scaleY;
    int B = b*scaleX;
    int H = h*scaleY;
    string tekst = "Paused";
    const char* txt = tekst.c_str();
    SDL_Color kleur = {255,255,255};
    SDL_Surface* st = TTF_RenderText_Solid(ltrtype,txt,kleur);
    SDL_Texture* tt = SDL_CreateTextureFromSurface(this->scherm,st);
    SDL_FreeSurface(st);

    SDL_Rect dstrect = {xP, yP, B, H};
    SDL_RenderCopy(this->scherm,tt, NULL, &dstrect);
}
void SDLFact::end(int choice, int x, int y, int b, int h, double scaleX, double scaleY)
{
    int xP = x*scaleX;
    int yP = y*scaleY;
    int B = b*scaleX;
    int H = h*scaleY;
    string tekst;
    switch (choice) {
        case 1:
            tekst = "You won!";
            Mix_PlayChannel(-1,winner,0);
            break;
        case -1:
            tekst = "You lost...";
            Mix_PlayChannel(-1,loser,0);
            break;
        default: break;
    }

    const char* txt = tekst.c_str();
    SDL_Color kleur = {0,255,0};
    SDL_Surface* st = TTF_RenderText_Solid(ltrtype,txt,kleur);
    SDL_Texture* tt = SDL_CreateTextureFromSurface(this->scherm,st);
    SDL_FreeSurface(st);

    ///Voeg nog dit toe
//    void close()
//    {
//        //Free loaded images
//        gPromptTexture.free();
//
//        //Free the sound effects
//        Mix_FreeChunk( gScratch );
//        Mix_FreeChunk( gHigh );
//        Mix_FreeChunk( gMedium );
//        Mix_FreeChunk( gLow );
//        gScratch = NULL;
//        gHigh = NULL;
//        gMedium = NULL;
//        gLow = NULL;
//
//        //Free the music
//        Mix_FreeMusic( gMusic );
//        gMusic = NULL;
//
//        //Destroy window
//        SDL_DestroyRenderer( gRenderer );
//        SDL_DestroyWindow( gWindow );
//        gWindow = NULL;
//        gRenderer = NULL;
//
//        //Quit SDL subsystems
//        Mix_Quit();
//        IMG_Quit();
//        SDL_Quit();
//    }
    Mix_Quit();
    SDL_Rect dstrect = {xP, yP, B, H};
    SDL_RenderCopy(this->scherm,tt, NULL, &dstrect);
    SDL_RenderPresent(this->scherm);
    SDL_Delay(5000);
}

void SDLFact::timer(int c, int x, int y, int b, int h, double scaleX, double scaleY) {
    string tekst = "Time: " + to_string(c);
    const char* txt = tekst.c_str();
    SDL_Color kleur = {255,255,255};
    SDL_Surface* st = TTF_RenderText_Solid(ltrtype,txt,kleur);
    SDL_Texture* tt = SDL_CreateTextureFromSurface(this->scherm,st);

    SDL_FreeSurface(st);

    if(c <= 10)
        kleur = {255,0,0,};
    int xP = x*scaleX;
    int yP = y*scaleY;
    int B = b*scaleX;
    int H = h*scaleY;

    SDL_Rect dstrect = {xP, yP, B, H};
    SDL_RenderCopy(this->scherm,tt, NULL, &dstrect);
}

void SDLFact::life(int c, int x, int y, int b, int h, double scaleX, double scaleY) {
    int xP = x*scaleX;
    int yP = y*scaleY;
    int B = b*scaleX;
    int H = h*scaleY;
    SDL_Rect dstrect;
    for(int i=0; i< c ; i++)
    {
        dstrect = {xP+B*2-i*B, yP, B, H};
        SDL_RenderCopy(this->scherm,life_heart,NULL,&dstrect);
    }
}
void SDLFact::bulletamount(int c, int x, int y, int b, int h, double scaleX, double scaleY) {
    string tekst = "Ammo: " + to_string(c);
    const char* txt = tekst.c_str();
    SDL_Color kleur = {255,255,255};
    SDL_Surface* st = TTF_RenderText_Solid(ltrtype,txt,kleur);
    SDL_Texture* tt = SDL_CreateTextureFromSurface(this->scherm,st);

    SDL_FreeSurface(st);

    if(c <= 3)
        kleur = {255,0,0,};
    int xP = x*scaleX;
    int yP = y*scaleY;
    int B = b*scaleX;
    int H = h*scaleY;

    SDL_Rect dstrect = {xP, yP, B, H};
    // cout << xP << " " << yP << " " << B << " " <<H<< endl;
    SDL_RenderCopy(this->scherm,tt, NULL, &dstrect);
}