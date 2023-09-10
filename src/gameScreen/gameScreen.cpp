#include "globals.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "stage.hpp"
#include "exit.hpp"
#include <raylib.h>

void updateState(GameState, Player*, Stage**, Exit*, Enemy*); // change state function in gameScreen/gameScreen.cpp

void gameScreen(void)
{
    Camera2D camera = {{SCREEN_W/2, SCREEN_H/2}, {0,0}, 0.0f, 1.0f}; // camera initialization
    
    Player player; // Player initialization
    player.setHeight(100);
    player.setWidth(50);

    Exit exit; // Exit initialization

    Stage* stagePtr = NULL; // Stage pointer

    updateState(GENERATION, &player, &stagePtr, &exit, NULL);

    while(true)
    {
        // Only process certain things depenging on the currentState
        if (currentState == PLAYING) 
        {
            // TODO: LOCK CAMERA AFTER PLAYER GETS TO A CERTAIN POINT NEAR WALL (LIMIT RANGE)
            camera.target = Vector2Lerp(camera.target, player.getPos(), 0.15);
            
            player.movePlayer();
            stagePtr->stageManager();

            if (player.getInvulnTime() == 0) // if we are NOT invulnerable
            {
                for (int i = 0; i < stagePtr->getMaxEnemies(); ++i) 
                {
                    if (stagePtr->getEnemiesArray()[i].getIsActive())
                    {
                        if (CheckCollisionRecs(player.getHitbox(), stagePtr->getEnemiesArray()[i].getHitbox()))
                        {
                            player.setEnemyReference(&stagePtr->getEnemiesArray()[i]);
                            player.setInvulnTime(INVULN_FRAMES);
                        } else if (CheckCollisionCircleRec(player.getAttackHitbox().center, player.getAttackHitbox().radius, stagePtr->getEnemiesArray()[i].getHitbox()))
                        {
                            updateState(COMBAT, &player, &stagePtr, &exit, &stagePtr->getEnemiesArray()[i]);
                        }
                    }
                }

                for (int j = 0; j < stagePtr->getMaxProjectiles(); ++j) 
                {
                    if (stagePtr->getProjectileArray()[j].getIsActive()) 
                    {
                        if (CheckCollisionRecs(player.getHitbox(), stagePtr->getProjectileArray()[j].getHitbox()))
                        {
                            player.setProjectileCollisionLocation(stagePtr->getProjectileArray()[j].getCenter());
                            player.setInvulnTime(INVULN_FRAMES);
                            stagePtr->getProjectileArray()[j].killProjectile();
                        } else if (CheckCollisionCircleRec(player.getAttackHitbox().center, player.getAttackHitbox().radius, stagePtr->getProjectileArray()[j].getHitbox()))
                        {
                            stagePtr->getProjectileArray()[j].killProjectile();
                        }
                    }
                }
            }
        } else if (currentState == COMBAT) 
        {
            
        } else if (currentState == DEATH) 
        {

        } else if (currentState == PURGATORY) 
        {
            // DO NOTHING (No processing)
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode2D(camera);

            if (stagePtr != NULL) 
            {
                stagePtr->drawStage();
            } else 
            {
                DrawRectangle(100, 100, 30, 30, PINK);  // DUBEG RECTANGLE
            }

            player.drawPlayer();

            EndMode2D();

            // Only draw certain things based on currentState
            if (currentState == PLAYING) 
            {
                DrawText("PLAYING", 10, 20, 50, GREEN);
                DrawText(TextFormat("Pos: %03i, %03i", (int)player.getPos().x, (int)player.getPos().y), 20, 80, 40, RED);
                DrawText(TextFormat("Attack Cooldown: %03i", (int)player.getAttackCooldown()), 20, 140, 40, RED);
                DrawText(TextFormat("Invuln Timer: %03i", (int)player.getInvulnTime()), 20, 200, 40, RED);
                DrawText(TextFormat("Enemy Respawn: %03i", (int)stagePtr->getEnemyRespawnTime()), 20, 260, 40, ORANGE);
                DrawText(TextFormat("Projectile Respawn: %03i", (int)stagePtr->getProjectileRespawnTime()), 20, 320, 40, ORANGE);
            } else if (currentState == COMBAT) 
            {
                DrawText("COMBAT", 10, 20, 50, GREEN);
                DrawText(TextFormat("Pos: %03i, %03i", (int)player.getPos().x, (int)player.getPos().y), 20, 80, 40, RED);
            } else if (currentState == DEATH) 
            {

            } else if (currentState == PURGATORY) 
            {
                // DO NOTHING (No processing)
            }
            
        EndDrawing();

        if (WindowShouldClose())
        {
            CloseWindow();

        }
    }
}

// Updates the currentState to the nextState
// Also handles one time execution of anything needing to happen on state change
void updateState(GameState nextState, Player* playerPtr, Stage** stagePtr, Exit* exitPtr, Enemy* enemyPtr) 
{
    previousState = currentState;
    currentState = nextState;

    if (nextState == GENERATION) 
    {
        if (*stagePtr != NULL) // delete old stage 
        {
            delete *stagePtr;
            *stagePtr = NULL;
        }
        // fetch a layout from file
        *stagePtr = new Stage(1000.0f, 1000.0f, playerPtr); // create stage object
        playerPtr->setPos({0,0}); // reset player
        exitPtr->setPos((*stagePtr)->getExitLocation()); // update exit location
        updateState(PLAYING, playerPtr, stagePtr, exitPtr, enemyPtr); // keep an eye on this, might cause issues
    } else if (nextState == PLAYING) 
    {
        // set a small amount of invulnerability
    } else if (nextState == COMBAT) 
    {

    } else if (nextState == DEATH) 
    {
        
    } else if (nextState == PURGATORY) 
    {

    }
}