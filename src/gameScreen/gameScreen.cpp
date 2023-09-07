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

// if (IsKeyDown(KEY_W))
// {
//     player.setDirection(NORTH);

// } else if (IsKeyDown(KEY_D))
// {
//     player.setDirection(EAST);

// } else if (IsKeyDown(KEY_A))
// {
//     player.setDirection(SOUTH);

// } else if (IsKeyDown(KEY_A))
// {
//     player.setDirection(WEST);

// }