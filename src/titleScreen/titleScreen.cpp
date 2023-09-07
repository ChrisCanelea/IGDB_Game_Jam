#include "globals.hpp"
#include <raylib.h>

void titleScreen(void)
{
    while(true)
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("Claustrophobia: Kill Shit to Survive", 10, 50, 50, RED);

            DrawRectangle(SCREEN_W/2 - 100, SCREEN_H/2 - 50, 200, 100, BLACK);
            DrawText("Play", SCREEN_W/2 - 50, SCREEN_H/2 - 25, 50, WHITE);

        EndDrawing();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            break;

        }

        if (WindowShouldClose())
        {
            CloseWindow();

        }
    }
}