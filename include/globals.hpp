#ifndef globals_hpp
#define globals_hpp

#include <raylib.h>
#include <raymath.h>

#include "player.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include "stage.hpp"

const int SCREEN_W = 1920;
const int SCREEN_H = 1080;

enum Direction {NORTH = 0, NORTHEAST = 1, EAST = 2, SOUTHEAST = 3, SOUTH = 4, SOUTHWEST = 5, WEST = 6, NORTHWEST = 7};

void titleScreen(void); // title screen loop located in titleScreen/titleScreen.cpp
void gameScreen(void); // game screen located in gameScreen/gameScreen.cpp

#endif // globals_hpp