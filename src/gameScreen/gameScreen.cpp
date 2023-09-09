#include "globals.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "stage.hpp"
#include <raylib.h>

void gameScreen(void)
{
    Player player;
    player.setHeight(50);
    player.setWidth(50);
    Camera2D camera = {{SCREEN_W/2, SCREEN_H/2}, {0,0}, 0.0f, 1.0f}; // camera initialization

    Stage test({-250, -250, 500, 500}, &player);
    
    Enemy enemy;
    enemy.setHeight(50);
    enemy.setWidth(50);
    enemy.setPos(Vector2 {50, 50});

    while(true)
    {
        camera.target = Vector2Lerp(camera.target, player.getPos(), 0.15);
        
        player.movePlayer();

        if (player.getInvulnTime() > 0)
        {
            if (player.getInvulnTime() > INVULN_FRAMES/2)
            {
                player.enemyKnockback(enemy);

            }

            player.setInvulnTime(player.getInvulnTime() - 1);

        } else if (CheckCollisionRecs(player.getHitbox(), enemy.getHitbox()))
        {
            player.setInvulnTime(INVULN_FRAMES);

        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(TextFormat("Pos: %03i, %03i", (int)player.getPos().x, (int)player.getPos().y), 20, 20, 20, BLUE);
            DrawText("Game", 10, 50, 50, RED);

            BeginMode2D(camera);

            player.drawPlayer();
            enemy.drawEnemy();

            EndMode2D();
        EndDrawing();

        if (WindowShouldClose())
        {
            CloseWindow();

        }
    }
}