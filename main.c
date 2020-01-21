#include "raylib.h"
#include "src/include/game.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

Game game = {500, 1, 1, 0, -1, 0, 0};

void main_loop() {
        update_game(&game);
        draw_game(&game);  
}

int main (int argc, char * argv[]) {

    #if defined(PLATFORM_WEB)
        srand(0);
    #endif

    InitWindow(SCREEN_W, SCREEN_H, "Mafia Slots");
    InitAudioDevice();   
  //  ToggleFullscreen();
    
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(&main_loop, 0, 1);
    #else
        SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        main_loop();
    }
    #endif

    CloseWindow();      

    return 0;   
}