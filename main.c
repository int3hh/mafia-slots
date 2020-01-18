#include "raylib.h"
#include "src/include/game.h"

Game game = {5000, 1, 1, 0, -1, 1, 1};

int main (int argc, char * argv[]) {

    InitWindow(SCREEN_W, SCREEN_H, "Mafia Slots");
    InitAudioDevice();   
   // ToggleFullscreen();
    SetTargetFPS(60);
    load_assets();

    while (!WindowShouldClose())   
    {
        update_game(&game);
        draw_game(&game);   
    }

    CloseWindow();      

    return 0;   
}