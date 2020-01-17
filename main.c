#include "raylib.h"
#include "src/include/game.h"

Game game = {0, 1, 1, 0};

int main (int argc, char * argv[]) {

    InitWindow(SCREEN_W, SCREEN_H, "Mafia Slots");
    SetTargetFPS(60);
    load_assets();

    while (!WindowShouldClose())   
    {
        update_game(&game);
        draw_game(game);   
    }

    CloseWindow();      

    return 0;   
}