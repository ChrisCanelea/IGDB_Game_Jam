g++ src/*.cpp src/titleScreen/*.cpp src/gameScreen/*.cpp classes/*.cpp -Wl,--subsystem,windows -mwindows -o game -Wall -I include -I classes -L lib -lraylib -lopengl32 -lgdi32 -lwinmm
@REM test