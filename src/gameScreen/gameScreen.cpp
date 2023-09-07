#include "globals.hpp"
#include "player.hpp"
#include <raylib.h>

void gameScreen(void)
{
    Player player;
    player.setHeight(50);
    player.setWidth(50);
    while(true)
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("Game", 10, 50, 50, RED);

            player.movePlayer();
            
            player.drawPlayer();

        EndDrawing();

        if (WindowShouldClose())
        {
            CloseWindow();

        }
    }
}