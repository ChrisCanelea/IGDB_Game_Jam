#include "globals.hpp"
#include <raylib.h>

int main(void)
{

    InitWindow(SCREEN_W, SCREEN_H, "title");
    ToggleFullscreen();
    SetTargetFPS(60);

    while(true)
    {
        titleScreen();
        gameScreen();

        if (WindowShouldClose())
        {
            CloseWindow();

        }
    }

}