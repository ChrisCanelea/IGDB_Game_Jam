#include "globals.hpp"
#include <raylib.h>
#include "optionScreen.hpp"


void titleScreen(void)
{
    int buttonState = 0; //button consists three states: 0 is not pressed, 1 is mouse hovering on top and 2 is pressed (for sound possibly)
    Rectangle playButtonBound = {SCREEN_W/2.0 - 100, SCREEN_H/2 - 150, 200, 100};        //x,y,w,h
    Rectangle optButtonBound = {SCREEN_W/2.0 - 100, SCREEN_H/2 - 50, 200, 50};
    Vector2 mousePos = {0.0,0.0};

    while(true)
    {

        BeginDrawing();
            ClearBackground(RAYWHITE);//initialize background
            
            mousePos = GetMousePosition(); //constantly getting mouse position

            
            DrawText("Claustrophobia: Kill Shit to Survive", 10, 50, 50, RED);

            if(CheckCollisionPointRec(mousePos,playButtonBound))
            {
                DrawRectangle(SCREEN_W/2 - 100, SCREEN_H/2 - 50, 200, 100, YELLOW);
                DrawText("Play", SCREEN_W/2 - 50, SCREEN_H/2 - 25, 50, RED);
            } else
            {
                DrawRectangle(SCREEN_W/2 - 100, SCREEN_H/2 - 50, 200, 100, BLACK);
                DrawText("Play", SCREEN_W/2 - 50, SCREEN_H/2 - 25, 50, WHITE);
            }

            if(CheckCollisionPointRec(mousePos, optButtonBound))
            {
                DrawText("Options", SCREEN_W/2.0 - 100, SCREEN_H/2 + 100, 50, RED);
            } else
            {
                DrawText("Options", SCREEN_W/2.0 - 100, SCREEN_H/2 + 100, 50, BLACK);
            }
        

        EndDrawing();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos,playButtonBound))
        {
            return;

        }else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos,optButtonBound))
        {
            optionScreen();
        }

        if (WindowShouldClose())
        {
            CloseWindow();
        }
    }
}
