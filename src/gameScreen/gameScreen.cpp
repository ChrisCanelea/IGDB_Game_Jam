#include "globals.hpp"
#include "player.hpp"
#include <raylib.h>

void gameScreen(void)
{
    Player player;
    while(true)
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("Game", 10, 50, 50, RED);

            player.drawPlayer();

        EndDrawing();

        if (WindowShouldClose())
        {
            CloseWindow();

        }
    }
}