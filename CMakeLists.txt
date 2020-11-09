cmake_minimum_required(VERSION 3.16)
project(Programmeren)

set(CMAKE_CXX_STANDARD 14)

add_executable(Programmeren main.cpp Abstract/AbstractFact.h Abstract/Entity.cpp Abstract/Entity.h Game.cpp Game.h SDL/SDLFact.cpp SDL/SDLFact.h Abstract/PlayerShip.cpp Abstract/PlayerShip.h SDL/SDLPlayerShip.cpp SDL/SDLPlayerShip.h Abstract/Event.cpp Abstract/Event.h SDL/SDLEvent.cpp SDL/SDLEvent.h Abstract/Bullet.cpp Abstract/Bullet.h SDL/SDLBullet.cpp SDL/SDLBullet.h Abstract/EnemyShip.cpp Abstract/EnemyShip.h SDL/SDLEnemyShip.cpp SDL/SDLEnemyShip.h Abstract/Bonus.cpp Abstract/Bonus.h SDL/SDLBonus.cpp SDL/SDLBonus.h)
target_link_libraries(Programmeren ${SDL2_LIBARY} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
