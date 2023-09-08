#include "globals.hpp"
#include "player.hpp"
#include <raylib.h>

void gameScreen(void)
{
    Player player;
    Camera2D camera = {{SCREEN_W/2, SCREEN_H/2}, {0,0}, 0.0f, 1.0f}; // camera initialization
    player.setHeight(50);
    player.setWidth(50);
    while(true)
    {
        camera.target = Vector2Lerp(camera.target, player.getPos(), 0.15);
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            BeginMode2D(camera);

            DrawText("Game", 10, 50, 50, RED);

            player.movePlayer();
            
            player.drawPlayer();

            EndMode2D();
        EndDrawing();

        if (WindowShouldClose())
        {
            CloseWindow();

        }
    }
}