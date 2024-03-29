#ifndef globals_hpp
#define globals_hpp

#include <raylib.h>
#include <raymath.h>

// comment out the below line when compiling for windows, uncomment when compiling for web
// #define PLATFORM_WEB

#if defined (PLATFORM_WEB)
    #include <../../../emsdk/upstream/emscripten/cache/sysroot/include/emscripten/emscripten.h>
#endif

const int SCREEN_W = 1920;
const int SCREEN_H = 1080;

const float ATTACK_OFFSET = 60;
const float ATTACK_RADIUS = 60;
const float ATTACK_FRAMES = 10;
const float ATTACK_COOLDOWN = 20;
const float INVULN_FRAMES = 30;
const float ENEMY_RESPAWN_TIME = 60;
const float PROJECTILE_RESPAWN_TIME = 40;
const int COMBAT_TIMER = 120;
const float SHRINK_ON_HIT = 35;
const int MAX_LIVES = 10;

enum spriteType {LEFT = 0, RIGHT = 1, LEFT_SWORD = 2, RIGHT_SWORD = 3, SWING = 4, SWING_RIGHT = 5};

const Vector2 THE_VOID = {-10000, -10000};

extern float musicVol;
extern float effectVol;
extern int stageNumber;
extern int lives;
extern int score;
extern int highScore;

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