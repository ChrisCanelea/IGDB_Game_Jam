#include <raylib.h>

int main(void)
{

    int SCREEN_W = 500;
    int SCREEN_H = 500;

    InitWindow(SCREEN_W, SCREEN_H, "title");

    SetTargetFPS(60);
    while(true)
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("TEST", SCREEN_W/5, 50, 50, RED);

            DrawRectangle(SCREEN_W/2 - 100, SCREEN_H/2 - 50, 200, 100, BLACK);
            DrawText("Play", SCREEN_W/2 - 50, SCREEN_H/2 - 25, 50, WHITE);

        EndDrawing();

        if (WindowShouldClose())
        {
            CloseWindow();

        }
    }

}