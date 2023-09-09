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
                if (CheckCollisionRecs(player.getHitbox(), stage1.getEnemiesArray()[i].getHitbox()))
                {
                    player.setEnemyReference(&stage1.getEnemiesArray()[i]);
                    player.setInvulnTime(INVULN_FRAMES);
                }
            }
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode2D(camera);

            stage1.drawStage();

            player.drawPlayer();

            EndMode2D();

            DrawText(TextFormat("Pos: %03i, %03i", (int)player.getPos().x, (int)player.getPos().y), 20, 20, 20, BLUE);
            DrawText(TextFormat("Respawntime: %03i", (int)stage1.getEnemyRespawnTime()), 20, 300, 20, ORANGE);
            DrawText("Game", 10, 50, 50, RED);
            
        EndDrawing();

        if (WindowShouldClose())
        {
            CloseWindow();

        }
    }
}