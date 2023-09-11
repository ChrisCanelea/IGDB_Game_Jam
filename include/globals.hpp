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
const float ENEMY_RESPAWN_TIME = 120;
const float PROJECTILE_RESPAWN_TIME = 120;
const int COMBAT_TIMER = 120;
const float SHRINK_ON_HIT = 35;

const Vector2 THE_VOID = {-10000, -10000};

static float musicVol = 100;
static float effectVol = 100;
extern int stageNumber;

// enum Direction {NORTH = 0, NORTHEAST = 1, EAST = 2, SOUTHEAST = 3, SOUTH = 4, SOUTHWEST = 5, WEST = 6, NORTHWEST = 7};
typedef enum GameState {GENERATION = 0, PLAYING, COMBAT, DEATH, PURGATORY} GameState;

extern GameState currentState;
extern GameState previousState;

// #include "player.hpp"
// #include "enemy.hpp"
// #include "projectile.hpp"
// #include "stage.hpp"

void titleScreen(void); // title screen loop located in titleScreen/titleScreen.cpp
void gameScreen(void); // game screen located in gameScreen/gameScreen.cpp

#endif // globals_hpp