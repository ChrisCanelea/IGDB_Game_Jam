#include "globals.hpp"
#include <raylib.h>
#include "optionScreen.hpp"



void titleScreen(void)
{
    //initializing audio device, prep buffer
    InitAudioDevice();
    Music menuTrack = LoadMusicStream("assets/Music/Main_menu.mp3");
    menuTrack.looping = true;
    PlayMusicStream(menuTrack);

    Texture2D titlePage = LoadTexture("assets/titlePage.png");

    Rectangle playButtonBound = {SCREEN_W/2 - 120, 800, 200, 100}; //x,y,w,h
    Rectangle optButtonBound = {SCREEN_W/2 - 120, 950, 200, 50};
    Vector2 mousePos = {0.0,0.0};

    while(true)
    {

        //update music buffer
        UpdateMusicStream(menuTrack);
        if(GetMusicTimePlayed(menuTrack)>=28.55)
        {
            SeekMusicStream(menuTrack,3.18);
            PlayMusicStream(menuTrack);
        }


        BeginDrawing();
            ClearBackground(RAYWHITE);//initialize background
            // DrawTexture(titlePage, 0, 0, WHITE);
            DrawTextureEx(titlePage, Vector2 {0, 0}, 0, 2, WHITE);
            
            mousePos = GetMousePosition(); //constantly getting mouse position

            
            DrawText("The Shrinking", SCREEN_W/2 - 450, 100, 80, RED);
            DrawText("Dungeon", SCREEN_W/2 - 450, 150, 80, RED);

            if(CheckCollisionPointRec(mousePos,playButtonBound))
            {
                DrawRectangleRec(playButtonBound, YELLOW);
                DrawText("Play", SCREEN_W/2  - 70, 825, 50, RED);
            } else
            {
                DrawRectangleRec(playButtonBound, BLACK);
                DrawText("Play", SCREEN_W/2  - 70, 825, 50, WHITE);
            }

            if(CheckCollisionPointRec(mousePos, optButtonBound))
            {
                DrawText("Options", SCREEN_W/2 - 110, 950, 50, RED);
            } else
            {
                DrawText("Options", SCREEN_W/2 - 110, 950, 50, BLACK);
            }
        

        EndDrawing();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos,playButtonBound))
        {
            return;

        }else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos,optButtonBound))
        {
            optionScreen(menuTrack);
        }

        if (WindowShouldClose())
        {
            UnloadMusicStream(menuTrack);
            CloseAudioDevice();
            CloseWindow();
        }
    }
}
