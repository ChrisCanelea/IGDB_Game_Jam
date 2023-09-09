#include "globals.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "stage.hpp"
#include <raylib.h>

void gameScreen(void)
{
    Player player;
    player.setHeight(100);
    player.setWidth(50);
    Camera2D camera = {{SCREEN_W/2, SCREEN_H/2}, {0,0}, 0.0f, 1.0f}; // camera initialization

    Stage stage1({-500, -500, 1000, 1000}, &player);

    while(true)
    {
        // TODO: LOCK CAMERA AFTER PLAYER GETS TO A CERTAIN POINT NEAR WALL (LIMIT RANGE)
        camera.target = Vector2Lerp(camera.target, player.getPos(), 0.15);
        
        player.movePlayer();
        stage1.stageManager();

        if (player.getInvulnTime() == 0) // if we are NOT invulnerable
        {
            for (int i = 0; i < stage1.getMaxEnemies(); ++i) 
            {
                if (stage1.getEnemiesArray()[i].getIsActive() && CheckCollisionRecs(player.getHitbox(), stage1.getEnemiesArray()[i].getHitbox()))
                {
                    player.setEnemyReference(&stage1.getEnemiesArray()[i]);
                    player.setInvulnTime(INVULN_FRAMES);
                }
            }

            for (int j = 0; j < stage1.getMaxProjectiles(); ++j) 
            {
                if (stage1.getProjectileArray()[j].getIsActive() && CheckCollisionRecs(player.getHitbox(), stage1.getProjectileArray()[j].getHitbox())) 
                {
                    player.setProjectileReference(&stage1.getProjectileArray()[j]);
                    player.setInvulnTime(INVULN_FRAMES);
                    stage1.getProjectileArray()[j].killProjectile();
                }
            }
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode2D(camera);

            stage1.drawStage();

            player.drawPlayer();

            EndMode2D();

            DrawText("Game", 10, 20, 50, GREEN);
            DrawText(TextFormat("Pos: %03i, %03i", (int)player.getPos().x, (int)player.getPos().y), 20, 80, 40, RED);
            DrawText(TextFormat("Attack Cooldown: %03i", (int)player.getAttackCooldown()), 20, 140, 40, RED);
            DrawText(TextFormat("Invuln Timer: %03i", (int)player.getInvulnTime()), 20, 200, 40, RED);
            DrawText(TextFormat("Enemy Respawn: %03i", (int)stage1.getEnemyRespawnTime()), 20, 260, 40, ORANGE);
            DrawText(TextFormat("Projectile Respawn: %03i", (int)stage1.getProjectileRespawnTime()), 20, 320, 40, ORANGE);
            
        EndDrawing();

        if (WindowShouldClose())
        {
            CloseWindow();

        }
    }
}