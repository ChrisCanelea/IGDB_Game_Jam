#include "globals.hpp"
#include "player.hpp"
#include <raylib.h>

void gameScreen(void)
{
    Player player;
    Camera2D camera = {{0,0}, {0,0}, 0.0f, 0.5f}; // camera initialization
    Vector2 cameraPos = {SCREEN_W/2, SCREEN_H/2};
    Vector2 cameraLerp;
    player.setHeight(50);
    player.setWidth(50);
    while(true)
    {
        cameraLerp = Vector2Lerp(cameraPos, player.getPos(), 0.15);
        camera.target = cameraLerp;
        cameraPos.x += cameraLerp.x;
        cameraPos.y += cameraLerp.y;
        
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