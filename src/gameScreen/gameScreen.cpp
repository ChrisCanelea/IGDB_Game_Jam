#include "globals.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "stage.hpp"
#include "exit.hpp"
#include <raylib.h>

void updateState(GameState, Player*, Stage*, Exit*, Enemy*); // change state function in gameScreen/gameScreen.cpp

void gameScreen(void)
{
    Camera2D camera = {{SCREEN_W/2, SCREEN_H/2}, {0,0}, 0.0f, 1.0f}; // camera initialization
    
    Player player; // Player initialization
    player.setHeight(100);
    player.setWidth(50);

    Exit exit; // Exit initialization

    Stage* stage = NULL; // Stage pointer

    updateState(GENERATION, &player, stage, &exit, NULL);

    while(true)
    {
        // TODO: LOCK CAMERA AFTER PLAYER GETS TO A CERTAIN POINT NEAR WALL (LIMIT RANGE)
        camera.target = Vector2Lerp(camera.target, player.getPos(), 0.15);
        
        player.movePlayer();
        stage->stageManager();

        if (player.getInvulnTime() == 0) // if we are NOT invulnerable
        {
            for (int i = 0; i < stage->getMaxEnemies(); ++i) 
            {
                if (stage->getEnemiesArray()[i].getIsActive())
                {
                    if (CheckCollisionRecs(player.getHitbox(), stage->getEnemiesArray()[i].getHitbox()))
                    {
                        player.setEnemyReference(&stage->getEnemiesArray()[i]);
                        player.setInvulnTime(INVULN_FRAMES);
                    } else if (CheckCollisionCircleRec(player.getAttackHitbox().center, player.getAttackHitbox().radius, stage->getEnemiesArray()[i].getHitbox()))
                    {
                        
                    }
                }
            }

            for (int j = 0; j < stage->getMaxProjectiles(); ++j) 
            {
                if (stage->getProjectileArray()[j].getIsActive()) 
                {
                    if (CheckCollisionRecs(player.getHitbox(), stage->getProjectileArray()[j].getHitbox()))
                    {
                        player.setProjectileCollisionLocation(stage->getProjectileArray()[j].getCenter());
                        player.setInvulnTime(INVULN_FRAMES);
                        stage->getProjectileArray()[j].killProjectile();
                    } else if (CheckCollisionCircleRec(player.getAttackHitbox().center, player.getAttackHitbox().radius, stage->getProjectileArray()[j].getHitbox()))
                    {
                        stage->getProjectileArray()[j].killProjectile();
                    }
                }
            }
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode2D(camera);

            stage->drawStage();

            player.drawPlayer();

            EndMode2D();

            DrawText("Game", 10, 20, 50, GREEN);
            DrawText(TextFormat("Pos: %03i, %03i", (int)player.getPos().x, (int)player.getPos().y), 20, 80, 40, RED);
            DrawText(TextFormat("Attack Cooldown: %03i", (int)player.getAttackCooldown()), 20, 140, 40, RED);
            DrawText(TextFormat("Invuln Timer: %03i", (int)player.getInvulnTime()), 20, 200, 40, RED);
            DrawText(TextFormat("Enemy Respawn: %03i", (int)stage->getEnemyRespawnTime()), 20, 260, 40, ORANGE);
            DrawText(TextFormat("Projectile Respawn: %03i", (int)stage->getProjectileRespawnTime()), 20, 320, 40, ORANGE);
            
        EndDrawing();

        if (WindowShouldClose())
        {
            CloseWindow();

        }
    }
}

// Updates the currentState to the nextState
// Also handles one time execution of anything needing to happen on state change
void updateState(GameState nextState, Player* player, Stage* stage, Exit* exit, Enemy* enemy) 
{
    previousState = currentState;
    currentState = nextState;

    if (nextState == GENERATION) 
    {
        if (stage != NULL) // delete old stage 
        {
            delete stage;
        }
        // fetch a layout from file
        stage = new Stage(1000.0f, 1000.0f, player); // create stage object
        // reset player
        // update exit location
        updateState(PLAYING, player, stage, exit, enemy); // keep an eye on this, might cause issues
    } else if (nextState == PLAYING) 
    {
        
    } else if (nextState == COMBAT) 
    {

    } else if (nextState == DEATH) 
    {
        
    } else if (nextState == PURGATORY) 
    {

    }
}