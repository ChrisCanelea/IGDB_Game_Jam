#include "globals.hpp"
#include "optionScreen.hpp"
#include <raylib.h>


void optionScreen(){
    Vector2 mousePos = {0.0,0.0};
    Rectangle musicVolumeSlideBound = {SCREEN_W/2.0 - 200, SCREEN_H/2 - 50, 400, 30};      //x,y,w,h
    Rectangle effectVolumeSlideBound = {SCREEN_W/2.0 - 200, SCREEN_H/2 + 80, 400, 30};     //x,y,w,h
    Rectangle returnBox = {5, 5, 105, 40};
    
    int musicRecWidth = 400;    //initializing the width of gray box, to be modified when mouse clicked
    int effectRecWidth = 400;
    int musicRecXPos = SCREEN_W/2 + 400;    //initializing the x coordinate of the gray box. to be modified when mouse clicked
    int effectRecXPos = SCREEN_W/2 + 400;


    while(1)
    {
        BeginDrawing();  
            ClearBackground(RAYWHITE);//initialize background
            mousePos = GetMousePosition(); //constantly getting mouse position


            //drawing music volume slider
            if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos,musicVolumeSlideBound))
            {
                musicRecXPos = (int) mousePos.x; //take the x position of the mouse and start filling white til the end of the box to create the slide effect
                musicRecWidth = musicRecXPos-(SCREEN_W/2-200);
            }
            DrawText("Music Volume", SCREEN_W/2 - 400, SCREEN_H/2 - 50, 30, BLACK);
            DrawRectangle(SCREEN_W/2 - 200, SCREEN_H/2 - 50, musicRecWidth, 30, BLUE);
            DrawRectangle(musicRecXPos, SCREEN_H/2-50, 400-musicRecWidth, 30, GRAY); 


            //drawing effect volume slider
            if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos,effectVolumeSlideBound))
            {
                effectRecXPos = (int) mousePos.x; //take the x position of the mouse and start filling white til the end of the box to create the slide effect
                effectRecWidth = effectRecXPos-(SCREEN_W/2-200);
            }
            DrawText("Effect Volume", SCREEN_W/2 - 420, SCREEN_H/2 + 80, 30, BLACK);
            DrawRectangle(SCREEN_W/2 - 200, SCREEN_H/2 + 80, effectRecWidth, 30, BLUE);
            DrawRectangle(effectRecXPos, SCREEN_H/2 + 80, 400-effectRecWidth, 30, GRAY); 


            //drawing exit button
            DrawRectangle(5, 5, 105, 40, RED);
            DrawText("Return",5,5,30,BLACK);
            if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos,returnBox))
            {
                return;
            }

        EndDrawing();
    }
}