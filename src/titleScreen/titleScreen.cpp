#include "globals.hpp"
#include <raylib.h>

void titleScreen(void)
{
    int buttonState = 0; //button consists three states: 0 is not pressed, 1 is mouse hovering on top and 2 is pressed
    Rectangle buttonBound = {SCREEN_W/2.0 - 100, SCREEN_H/2 - 50, 200, 100};
    Vector2 mousePos = {0.0,0.0};

    while(true)
    {

        BeginDrawing();
            ClearBackground(RAYWHITE);//initialize background
            
            mousePos = GetMousePosition(); //constantly getting mouse position

            
            DrawText("Claustrophobia: Kill Shit to Survive", 10, 50, 50, RED);

            if(CheckCollisionPointRec(mousePos,buttonBound)){
                DrawRectangle(SCREEN_W/2 - 100, SCREEN_H/2 - 50, 200, 100, YELLOW);
                DrawText("Play", SCREEN_W/2 - 50, SCREEN_H/2 - 25, 50, RED);
            }else{
                DrawRectangle(SCREEN_W/2 - 100, SCREEN_H/2 - 50, 200, 100, BLACK);
                DrawText("Play", SCREEN_W/2 - 50, SCREEN_H/2 - 25, 50, WHITE);
            }
        

        EndDrawing();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos,buttonBound))
        {
            break;

        }

        if (WindowShouldClose())
        {
            CloseWindow();

        }
    }
}