#include "globals.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "stage.hpp"
#include "exit.hpp"
#include <raylib.h>

GameState currentState = PURGATORY;
GameState previousState = PURGATORY;
int stageNumber = 0;
int lives = 0;

void updateState(GameState, Player*, Stage**, Exit*, Enemy*, Camera2D*); // change state function in gameScreen/gameScreen.cpp

void gameScreen(void)
{
    Music musicTutorial = LoadMusicStream("assets/Music/Loopable_Tutorial.mp3");
    Music musicLevel1 = LoadMusicStream("assets/Music/Level_Track_1.mp3");
    Music musicLevel2 = LoadMusicStream("assets/Music/Level_Track_2.mp3");
    Music musicLevel3 = LoadMusicStream("assets/Music/Level_Track_3.mp3");
    Music* currentMusic = NULL;
    bool inSecondLoop = false;
    int stageReached = 0;
    int killsReached = 0;
    int kills = 0;

    Sound swingMisses[3];
    swingMisses[0] = LoadSound("Sword_Swoosh_light_1.mp3");
    swingMisses[1] = LoadSound("Sword_Swoosh_light_2.mp3");
    swingMisses[2] = LoadSound("Sword_Swoosh_light_3.mp3");

    Sound swingHits[2];
    swingHits[0] = LoadSound("Sword_Swoosh_heavy_1.mp3");
    swingHits[1] = LoadSound("Sword_Swoosh_heavy_2.mp3");

    Sound swingEnemy = LoadSound("Sword_Swoosh_enemy.mp3");
    Sound swingKill = LoadSound("Sword_Swoosh_kill.mp3");

    Camera2D camera = {{SCREEN_W/2, SCREEN_H/2}, {0,0}, 0.0f, 1.0f}; // camera initialization
    
    Player player; // Player initialization
    player.setHeight(96);
    player.setWidth(69);

    Exit exit; // Exit initialization

    Stage* stagePtr = NULL; // Stage pointer

    musicTutorial.looping = true;
    currentMusic = &musicTutorial;
    PlayMusicStream(*currentMusic);
    updateState(GENERATION, &player, &stagePtr, &exit, NULL, &camera);

    while(true)
    {
        // MUSIC STREAM HANDLING
        // track lengths given by raylib: 40.4879, 40.4879, 43.6767
        if (stageNumber <= 1) // in tutorial
        {
            SetMusicVolume(*currentMusic, musicVol/100.0);
            UpdateMusicStream(*currentMusic);
        } else 
        {
            if (IsMusicStreamPlaying(musicTutorial)) // if tutorial music is still playing (only happens once)
            {
                StopMusicStream(musicTutorial); // stop it
                currentMusic = &musicLevel1; // change to track 1
                PlayMusicStream(*currentMusic); // play it
            }

            if (currentMusic == &musicLevel1) // if track 1 is playing
            {
                if (!inSecondLoop && (GetMusicTimePlayed(*currentMusic) >= 40.4f)) // if at end of first loop
                {
                    SeekMusicStream(*currentMusic, 10.10f); // loop to end of intro
                    inSecondLoop = true; // update status variable
                } else if ((GetMusicTimePlayed(*currentMusic) >= 40.4f)) // if at end of second loop
                {
                    StopMusicStream(*currentMusic); // stop this track
                    currentMusic = &musicLevel2; // change to track 2
                    PlayMusicStream(*currentMusic); // play it
                    inSecondLoop = false; // reset status variable
                }
            } else if (currentMusic == &musicLevel2) // if track 2 is playing
            {
                if (!inSecondLoop && (GetMusicTimePlayed(*currentMusic) >= 40.4f)) // if at end of first loop
                {
                    SeekMusicStream(*currentMusic, 10.10f); // loop to end of intro
                    inSecondLoop = true; // update status variable
                } else if ((GetMusicTimePlayed(*currentMusic) >= 40.4f)) // if at end of second loop
                {
                    StopMusicStream(*currentMusic); // stop this track
                    currentMusic = &musicLevel3; // change to track 3
                    PlayMusicStream(*currentMusic); // play it
                    inSecondLoop = false; // reset status variable
                }
            } else // track 3 is playing
            {
                if (!inSecondLoop && (GetMusicTimePlayed(*currentMusic) >= 43.6f)) // if at end of first loop
                {
                    SeekMusicStream(*currentMusic, 5.45f); // loop to end of intro
                    inSecondLoop = true; // update status variable
                } else if ((GetMusicTimePlayed(*currentMusic) >= 43.6f)) // if at end of second loop
                {
                    StopMusicStream(*currentMusic); // stop this track
                    currentMusic = &musicLevel1; // change to track 1
                    PlayMusicStream(*currentMusic); // play it
                    inSecondLoop = false; // reset status variable
                }
            }

            // update stream with current song and adjust its volume
            SetMusicVolume(*currentMusic, musicVol/100.0);
            UpdateMusicStream(*currentMusic);

        }
        
        // Only process certain things depenging on the currentState
        if (currentState == PLAYING) 
        {
            if (IsKeyPressed(KEY_P)) 
            {
                updateState(PURGATORY, &player, &stagePtr, &exit, NULL, &camera);
            }

            if ((lives < 0) || !CheckCollisionPointRec(player.getPos(), stagePtr->getPlayArea()) || !CheckCollisionPointRec(Vector2 {player.getPos().x + player.getWidth(), player.getPos().y + player.getHeight()}, stagePtr->getPlayArea()))
            {
                stageReached = stageNumber;
                killsReached = kills;
                kills = 0;
                updateState(DEATH, &player, &stagePtr, &exit, NULL, &camera);
            }

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
                            PlaySound(swingEnemy);
                            player.setEnemyReference(&stagePtr->getEnemiesArray()[i]);
                            player.setInvulnTime(INVULN_FRAMES);
                            lives--;

                            stagePtr->setShrinkRate(stagePtr->getInitialShrinkRate() * 4); // quadruple shrink rate
                            stagePtr->setShrinkTimer(INVULN_FRAMES); // during invuln frames
                        
                        } else if (CheckCollisionCircleRec(player.getAttackHitbox().center, player.getAttackHitbox().radius, stagePtr->getEnemiesArray()[i].getHitbox()))
                        {
                            PlaySound(swingHits[GetRandomValue(0,1)]);
                            player.setEnemyReference(&stagePtr->getEnemiesArray()[i]);
                            updateState(COMBAT, &player, &stagePtr, &exit, &stagePtr->getEnemiesArray()[i], &camera);
                        } else if (player.getAttackCooldown() == ATTACK_COOLDOWN) 
                        {
                            PlaySound(swingMisses[(GetRandomValue(0,2))]);
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
                            lives--;
                            
                            stagePtr->setShrinkRate(stagePtr->getInitialShrinkRate() * 3); // triple the shrink rate
                            stagePtr->setShrinkTimer(INVULN_FRAMES); // during invuln frames
                        
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
                    ++kills;
                    PlaySound(swingKill);
                    player.getEnemyReference()->killEnemy();
                    player.setEnemyReference(NULL);
                    stagePtr->setShrinkRate(stagePtr->getInitialShrinkRate() * -8); // grow
                    stagePtr->setShrinkTimer(INVULN_FRAMES); // during invuln frames

                } else
                {
                    // player has lost the combat sequence
                    PlaySound(swingEnemy);
                    stagePtr->setShrinkRate(stagePtr->getInitialShrinkRate() * 8); // sextuple shrink rate
                    stagePtr->setShrinkTimer(INVULN_FRAMES); // during invuln frames
                    player.setInvulnTime(INVULN_FRAMES);
                    lives--;
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
                updateState(previousState, &player, &stagePtr, &exit, player.getEnemyReference(), &camera);
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

                player.drawPlayer();

                EndMode2D();
                
                DrawText(TextFormat("Stage: %03i", stageNumber), 10, 20, 50, RED);
                DrawText(TextFormat("Lives: %03i", lives), 10, 80, 50, RED);
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

                player.drawPlayer();
                player.getEnemyReference()->drawBlockIndicator();

                DrawText(TextFormat("%-3.2f", (((double)player.getCombatTimer()/60.0) >= 0)?((double)player.getCombatTimer()/60.0):(0.00)), player.getEnemyReference()->getPos().x + 10, player.getEnemyReference()->getPos().y - 30, 40, GREEN);

                EndMode2D();

                DrawText(TextFormat("Stage: %03i", stageNumber), 10, 20, 50, RED);
                DrawText(TextFormat("Lives: %03i", lives), 10, 80, 50, RED);
            } else if (currentState == DEATH) 
            {
                ClearBackground(BLACK);
                DrawText("You Died", SCREEN_W/2-200, 100, 100, RED);
                DrawText(TextFormat("Stage Reached:  %i", stageReached), SCREEN_W/2-350, 400, 70, RED);
                DrawText(TextFormat("Total kills:  %i", killsReached), SCREEN_W/2-350, 500, 70, RED);
                DrawText(TextFormat("Total score:  %i", killsReached * (stageReached * 10)), SCREEN_W/2-350, 600, 70, RED);
                DrawText("Press R to restart", SCREEN_W/2-350, 900, 70, RED);
            } else if (currentState == PURGATORY) 
            {
                DrawText("Paused", SCREEN_W/2-200, 100, 100, RED);
                DrawText("Press P to unpause", SCREEN_W/2-350, 200, 70, RED);

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
        lives = 3;

        cameraPtr->target = {0,0}; // move camera to origin

        if (*stagePtr != NULL) // delete old stage 
        {
            delete *stagePtr;
            *stagePtr = NULL;
        }

        // WIDTH AND HEIGHT IN CONSTRUCTOR ARE THE WIDTH AND HEIGHT OF THE BORDER (KEEP THEM AS A SQUARE)
        // Stage(float width, float height, int maxenemies, int maxprojectiles, int initialenemies, float shrinkrate, player playerreference)
        float prevSize = 1000.0f;
        float prevRate = 0.75f;

        if (stageNumber > 1) // not tutorial stage
        {
            // EDIT THIS TO BE BASED ON STAGENUMBER
            *stagePtr = new Stage(Lerp(prevSize, 500.0f, 0.25), Lerp(prevSize, 500.0f, 0.25), (stageNumber > 8)?(14):(6 + stageNumber), (stageNumber > 6)?(20):(10 + stageNumber), (stageNumber > 5)?(5):(stageNumber), prevRate = Lerp(prevRate, 1.5f, 0.25), playerPtr, exitPtr);
            prevSize = Lerp(prevSize, 500.0f, 0.25);
            prevRate = Lerp(prevRate, 1.5f, 0.25);
        } else // tutorial
        {
            *stagePtr = new Stage(1000.0f, 1000.0f, 2, 1, 1, 0.75, playerPtr, exitPtr); // create tutorial stage
        }

        playerPtr->setPos({0,0}); // reset player
        exitPtr->setPos((*stagePtr)->getExitLocation()); // update exit location
        playerPtr->setInvulnTime(INVULN_FRAMES);
        updateState(PLAYING, playerPtr, stagePtr, exitPtr, enemyPtr, cameraPtr); // keep an eye on this, might cause issues
    } else if (nextState == PLAYING) 
    {

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
        } else
        {
            stageNumber = 0;
        }
    } else if (nextState == PURGATORY) 
    {

    }
}