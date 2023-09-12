#include "globals.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "stage.hpp"
#include "exit.hpp"
#include <raylib.h>

GameState currentState = PURGATORY;
GameState previousState = PURGATORY;
int stageNumber = 0;

void updateState(GameState, Player*, Stage**, Exit*, Enemy*, Camera2D*); // change state function in gameScreen/gameScreen.cpp

void gameScreen(void)
{
    Camera2D camera = {{SCREEN_W/2, SCREEN_H/2}, {0,0}, 0.0f, 1.0f}; // camera initialization
    
    Player player; // Player initialization
    player.setHeight(96);
    player.setWidth(69);

    Exit exit; // Exit initialization

    Stage* stagePtr = NULL; // Stage pointer

    updateState(GENERATION, &player, &stagePtr, &exit, NULL, &camera);

    while(true)
    {
        // Only process certain things depenging on the currentState
        if (currentState == PLAYING) 
        {
            if (IsKeyPressed(KEY_P)) 
            {
                updateState(PURGATORY, &player, &stagePtr, &exit, NULL, &camera);
            }

            if (!CheckCollisionPointRec(player.getPos(), stagePtr->getPlayArea()) || !CheckCollisionPointRec(Vector2 {player.getPos().x + player.getWidth(), player.getPos().y + player.getHeight()}, stagePtr->getPlayArea()))
            {
                updateState(DEATH, &player, &stagePtr, &exit, NULL, &camera);
            }

            // TODO: LOCK CAMERA AFTER PLAYER GETS TO A CERTAIN POINT NEAR WALL (LIMIT RANGE)
            camera.target = Vector2Lerp(camera.target, player.getCenter(), 0.15);
            camera.zoom = Lerp(camera.zoom, 1.0f, 0.2f);
            
            player.movePlayer();
            stagePtr->stageManager();

            if (CheckCollisionRecs(player.getHitbox(), exit.getHitbox())) // exit touched
            {
                updateState(GENERATION, &player, &stagePtr, &exit, NULL, &camera);
            }

            if (player.getInvulnTime() == 0) // if we are NOT invulnerable
            {
                for (int i = 0; i < stagePtr->getMaxEnemies(); ++i) 
                {
                    if (stagePtr->getEnemiesArray()[i].getIsActive() && (player.getInvulnTime() == 0))
                    {
                        if (CheckCollisionRecs(player.getHitbox(), stagePtr->getEnemiesArray()[i].getHitbox()))
                        {
                            player.setEnemyReference(&stagePtr->getEnemiesArray()[i]);
                            player.setInvulnTime(INVULN_FRAMES);

                            stagePtr->setShrinkRate(stagePtr->getShrinkRate() * SHRINK_ON_HIT); // shrink on enemy hit
                        
                        } else if (CheckCollisionCircleRec(player.getAttackHitbox().center, player.getAttackHitbox().radius, stagePtr->getEnemiesArray()[i].getHitbox()))
                        {
                            player.setEnemyReference(&stagePtr->getEnemiesArray()[i]);
                            updateState(COMBAT, &player, &stagePtr, &exit, &stagePtr->getEnemiesArray()[i], &camera);
                        }
                    }
                }

                for (int j = 0; j < stagePtr->getMaxProjectiles(); ++j) 
                {
                    if (stagePtr->getProjectileArray()[j].getIsActive()) 
                    {
                        if (CheckCollisionRecs(player.getHitbox(), stagePtr->getProjectileArray()[j].getHitbox()) && (player.getInvulnTime() == 0))
                        {
                            player.setProjectileCollisionLocation(stagePtr->getProjectileArray()[j].getCenter());
                            player.setInvulnTime(INVULN_FRAMES);
                            stagePtr->getProjectileArray()[j].killProjectile();
                            
                            stagePtr->setShrinkRate(stagePtr->getShrinkRate() * SHRINK_ON_HIT/2); // shrink on projectile hit
                        
                        } else if (CheckCollisionCircleRec(player.getAttackHitbox().center, player.getAttackHitbox().radius, stagePtr->getProjectileArray()[j].getHitbox()))
                        {
                            stagePtr->getProjectileArray()[j].killProjectile();
                        }
                    }
                }
            }
        } else if (currentState == COMBAT) 
        {
            camera.target = Vector2Lerp(camera.target, player.getEnemyReference()->getCenter(), 0.15);
            camera.zoom = Lerp(camera.zoom, 2.5f, 0.2f);
            
            if (IsKeyPressed(KEY_P)) 
            {
                updateState(PURGATORY, &player, &stagePtr, &exit, NULL, &camera);
            }
            
            if (player.getCombatTimer() > 0)
            {
                player.pollDirectionAttacking();
                player.setCombatTimer(player.getCombatTimer() - 1);

            } else
            {
                if (!Vector2Equals(player.getDirectionAttacking(), player.getEnemyReference()->getDirectionBlocking()))
                {
                    // player has won the combat sequence
                    player.getEnemyReference()->killEnemy();
                    player.setEnemyReference(NULL);
                    stagePtr->setShrinkRate(stagePtr->getShrinkRate() * (-15 * SHRINK_ON_HIT));

                } else
                {
                    // player has lost the combat sequence
                    stagePtr->setShrinkRate(stagePtr->getShrinkRate() * SHRINK_ON_HIT);
                }
                updateState(PLAYING, &player, &stagePtr, &exit, player.getEnemyReference(), &camera);
            }

        } else if (currentState == DEATH) 
        {
            if (IsKeyPressed(KEY_R))
            {
                updateState(GENERATION, &player, &stagePtr, &exit, NULL, &camera);
            }
        } else if (currentState == PURGATORY) 
        {
            // DO NOTHING (No processing)
            Rectangle optButtonBound = {SCREEN_W/2.0 - 100, SCREEN_H/2 + 100, 200, 50};
            if(IsKeyPressed(KEY_P))
            {
                updateState(previousState, &player, &stagePtr, &exit, NULL, &camera);
            }
        }

        BeginDrawing();

            // Only draw certain things based on currentState
            if (currentState == PLAYING) 
            {
                ClearBackground(BLACK);
                BeginMode2D(camera);

                if (stagePtr != NULL) 
                {
                    stagePtr->drawStage();
                } else 
                {
                    DrawRectangle(100, 100, 30, 30, PINK);  // DUBEG RECTANGLE
                }

                // exit.drawExit();
                Rectangle tempExitRec = GetCollisionRec(exit.getHitbox(), stagePtr->getPlayArea());
                float xOffset = 0;
                float yOffset = 0;
                if (exit.getPos().x <= stagePtr->getPlayArea().x) 
                {
                    xOffset = stagePtr->getPlayArea().x - exit.getPos().x;
                }
                if (exit.getPos().y <= stagePtr->getPlayArea().y) 
                {
                    yOffset = stagePtr->getPlayArea().y - exit.getPos().y;
                }
                DrawTextureRec(exit.getSprite(), {0 + xOffset,0 + yOffset,tempExitRec.width,tempExitRec.height}, {tempExitRec.x, tempExitRec.y}, WHITE);

                player.drawPlayer();

                EndMode2D();
                
                DrawText(TextFormat("Stage: %03i", stageNumber), 10, 20, 50, RED);
                DrawText("PLAYING", 1700, 20, 50, GREEN);
                DrawText(TextFormat("Pos: %03i, %03i", (int)player.getPos().x, (int)player.getPos().y), 20, 80, 40, RED);
                DrawText(TextFormat("Attack Cooldown: %03i", (int)player.getAttackCooldown()), 20, 140, 40, RED);
                DrawText(TextFormat("Invuln Timer: %03i", (int)player.getInvulnTime()), 20, 200, 40, RED);
                DrawText(TextFormat("Enemy Respawn: %03i", (int)stagePtr->getEnemyRespawnTime()), 20, 260, 40, ORANGE);
                DrawText(TextFormat("Projectile Respawn: %03i", (int)stagePtr->getProjectileRespawnTime()), 20, 320, 40, ORANGE);
                DrawText(TextFormat("Atk hitbox: %03i, %03i", (int)player.getAttackHitbox().center.x, (int)player.getAttackHitbox().center.y),  20, 380, 40, ORANGE);
                DrawText(TextFormat("Combat Timer: %03i", player.getCombatTimer()), 20, 440, 40, ORANGE);
            } else if (currentState == COMBAT) 
            {
                ClearBackground(BLACK);
                BeginMode2D(camera);

                if (stagePtr != NULL) 
                {
                    stagePtr->drawStage();
                } else 
                {
                    DrawRectangle(100, 100, 30, 30, PINK);  // DUBEG RECTANGLE
                }

                Rectangle tempExitRec = GetCollisionRec(exit.getHitbox(), stagePtr->getPlayArea());
                exit.drawExit();
                //DrawTexturePro(exit.getSprite(), {exit.getHitbox().x + stagePtr->getPlayArea().x, }, tempExitRec, {0,0}, 0, WHITE)

                player.drawPlayer();
                player.getEnemyReference()->drawBlockIndicator();

                EndMode2D();

                DrawText(TextFormat("Stage: %03i", stageNumber), 10, 20, 50, RED);
                DrawText("COMBAT", 1700, 20, 50, GREEN);
                DrawText(TextFormat("Pos: %03i, %03i", (int)player.getPos().x, (int)player.getPos().y), 20, 80, 40, RED);
                DrawText(TextFormat("Attack Cooldown: %03i", (int)player.getAttackCooldown()), 20, 140, 40, RED);
                DrawText(TextFormat("Invuln Timer: %03i", (int)player.getInvulnTime()), 20, 200, 40, RED);
                DrawText(TextFormat("Enemy Respawn: %03i", (int)stagePtr->getEnemyRespawnTime()), 20, 260, 40, ORANGE);
                DrawText(TextFormat("Projectile Respawn: %03i", (int)stagePtr->getProjectileRespawnTime()), 20, 320, 40, ORANGE);
                DrawText(TextFormat("Atk hitbox: %03i, %03i", (int)player.getAttackHitbox().center.x, (int)player.getAttackHitbox().center.y),  20, 380, 40, ORANGE);
                DrawText(TextFormat("Combat Timer: %03i", player.getCombatTimer()), 20, 440, 40, ORANGE);
                DrawText(TextFormat("EnemyBlockDirection: %03f, %03f", player.getEnemyReference()->getDirectionBlocking().x, player.getEnemyReference()->getDirectionBlocking().y), 20, 500, 40, ORANGE);
                DrawText(TextFormat("PlayerAttackDirection: %03f, %03f", player.getDirectionAttacking().x, player.getDirectionAttacking().y), 20, 560, 40, ORANGE);
            } else if (currentState == DEATH) 
            {
                ClearBackground(BLACK);
                DrawText("You Died", SCREEN_W/2-200, 100, 100, RED);
                DrawText("press r to restart", SCREEN_W/2-350, 200, 70, RED);
            } else if (currentState == PURGATORY) 
            {
                DrawText("Paused", SCREEN_W/2-200, 100, 100, RED);
                DrawText("press p to unpause", SCREEN_W/2-350, 200, 70, RED);

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
void updateState(GameState nextState, Player* playerPtr, Stage** stagePtr, Exit* exitPtr, Enemy* enemyPtr, Camera2D* cameraPtr) 
{
    previousState = currentState;
    currentState = nextState;

    if (nextState == GENERATION) 
    {
        ++stageNumber; // increment stageNumber

        cameraPtr->target = {0,0}; // move camera to origin

        if (*stagePtr != NULL) // delete old stage 
        {
            delete *stagePtr;
            *stagePtr = NULL;
        }

        // fetch a layout from file potentially

        // WIDTH AND HEIGHT IN CONSTRUCTOR ARE THE WIDTH AND HEIGHT OF THE BORDER (KEEP THEM AS A SQUARE)
        if (stageNumber > 1) // not tutorial stage
        {
            // EDIT THIS TO BE BASED ON STAGENUMBER
            *stagePtr = new Stage(2000.0f, 2000.0f, playerPtr);
        } else // tutorial
        {
            *stagePtr = new Stage(1000.0f, 1000.0f, 1, 1, 1, playerPtr); // create stage object
        }

        playerPtr->setPos({0,0}); // reset player
        exitPtr->setPos((*stagePtr)->getExitLocation()); // update exit location
        updateState(PLAYING, playerPtr, stagePtr, exitPtr, enemyPtr, cameraPtr); // keep an eye on this, might cause issues
    } else if (nextState == PLAYING) 
    {
        // set a small amount of invulnerability
        if(previousState != PURGATORY)
        {
        playerPtr->setInvulnTime(INVULN_FRAMES);
        }
    } else if (nextState == COMBAT) 
    {
        playerPtr->setCombatTimer(COMBAT_TIMER);
        enemyPtr->generateDirectionBlocking();
        playerPtr->setDirectionAttacking(enemyPtr->getDirectionBlocking());
        playerPtr->setAttackHitbox(Circle {THE_VOID, 0});

    } else if (nextState == DEATH) 
    {
        if (stageNumber != 1)
        {
            stageNumber = 1;
        } else{
            stageNumber = 0;
        }
    } else if (nextState == PURGATORY) 
    {

    }
}