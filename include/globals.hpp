#ifndef globals_hpp
#define globals_hpp

#include <raylib.h>
#include <raymath.h>

const int SCREEN_W = 1920;
const int SCREEN_H = 1080;
const float ATTACK_OFFSET = 50;
const float ATTACK_RADIUS = 50;
const float ATTACK_FRAMES = 10;
const float ATTACK_COOLDOWN = 25;
const float INVULN_FRAMES = 30;
const float ENEMY_RESPAWN_TIME = 600;
const float PROJECTILE_RESPAWN_TIME = 600;

// enum Direction {NORTH = 0, NORTHEAST = 1, EAST = 2, SOUTHEAST = 3, SOUTH = 4, SOUTHWEST = 5, WEST = 6, NORTHWEST = 7};

// #include "player.hpp"
// #include "enemy.hpp"
// #include "projectile.hpp"
// #include "stage.hpp"

void titleScreen(void); // title screen loop located in titleScreen/titleScreen.cpp
void gameScreen(void); // game screen located in gameScreen/gameScreen.cpp

#endif // globals_hpp