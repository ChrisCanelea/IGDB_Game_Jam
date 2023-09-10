#include "globals.hpp"
#include <raylib.h>
#include "optionScreen.hpp"


void titleScreen(void)
{
    InitAudioDevice();
    Music menuTrack = LoadMusicStream("assets/Music/Main_menu.mp3");
    menuTrack.looping = false;

    SetMusicVolume(menuTrack,musicVol/100.0);
    //SeekMusicStream(menuTrack,3.18);
    PlayMusicStream(menuTrack);
    float titleMusicLen = GetMusicTimeLength(menuTrack);

    Rectangle playButtonBound = {SCREEN_W/2.0 - 100, SCREEN_H/2 - 50, 200, 100};        //x,y,w,h
    Rectangle optButtonBound = {SCREEN_W/2.0 - 100, SCREEN_H/2 + 100, 200, 50};
    Vector2 mousePos = {0.0,0.0};

    while(true)
    {

        UpdateMusicStream(menuTrack);
        
        // if(GetMusicTimePlayed(menuTrack)==titleMusicLen)
        // {
        //     CloseWindow();
        //     // SeekMusicStream(menuTrack,3.18);
        //     // PlayMusicStream(menuTrack);
        // }


        BeginDrawing();
            ClearBackground(RAYWHITE);//initialize background
            
            mousePos = GetMousePosition(); //constantly getting mouse position

            
            DrawText("Claustrophobia: Kill Shit to Survive", 10, 50, 50, RED);

            if(CheckCollisionPointRec(mousePos,playButtonBound))
            {
                DrawRectangleRec(playButtonBound, YELLOW);
                DrawText("Play", SCREEN_W/2 - 50, SCREEN_H/2 - 25, 50, RED);
            } else
            {
                DrawRectangleRec(playButtonBound, BLACK);
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
            UnloadMusicStream(menuTrack);
            CloseAudioDevice();
            CloseWindow();
        }
    }
}
