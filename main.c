#include "raylib.h"
#include "src/include/game.h"
#include <stdio.h>
#include <stdlib.h>

Game game = {500, 1, 1, 0, -1, 0, 0};

int main (int argc, char * argv[]) {

    InitWindow(SCREEN_W, SCREEN_H, "Mafia Slots");
    InitAudioDevice();   
    ToggleFullscreen();
    SetTargetFPS(60);
    load_assets();
    for (int i = 0; i < REEL_ROW; i++) {
        spin(&game);
    }

    while (!WindowShouldClose())   
    {
        update_game(&game);
        draw_game(&game);   
    }

    CloseWindow();      

    return 0;   
}