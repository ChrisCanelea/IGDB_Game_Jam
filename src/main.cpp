#include "globals.hpp"
#include <raylib.h>

int highScore = 0;

int main(void)
{

    InitWindow(SCREEN_W, SCREEN_H, "game title"); // change title
    ToggleFullscreen();

    // InitAudioDevice();

    // SetTargetFPS(60);

    // Load highScore from save data

    while(true)
    {
        titleScreen();
        gameScreen();

        if (WindowShouldClose())
        {
            // CloseAudioDevice();
            CloseWindow();
        }
    }

}