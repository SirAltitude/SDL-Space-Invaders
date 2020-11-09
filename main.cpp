#include <iostream>
#include "Abstract/AbstractFact.h"
#include "Game.h"
#include "SDL/SDLFact.h"

int main(int argc, char* args[]) {
    AbstractFact* A = new SDLFact();
    Game* G = new Game(A);
    G->run();
    return 0;
}
