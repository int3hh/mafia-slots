#include "include/game.h"
#include "raylib.h"

Texture2D Images[GFX_END];

void load_assets () {

    char gfx_filez[GFX_END][255] = {"assets/images/logo.png"};

    // Loading graphics 
    for (int i = 0; i < GFX_END; i++) {
        Images[i] = LoadTexture(gfx_filez[i]);
    }
}

void update_game (Game * game) {
    switch (game->screen)
    {
    case SCREEN_SPLASH:
        if (GetTime() > 2) {
            game->screen = SCREEN_GAME;
        }
        break;
    
    default:
        break;
    }
}

void draw_game (Game game) {
      BeginDrawing();

      switch (game.screen) {
          case SCREEN_SPLASH:
            ClearBackground(BLACK);
            DrawTexture(Images[GFX_LOGO], SCREEN_W / 2 - (Images[GFX_LOGO].height*2)  , SCREEN_H / 2 - Images[GFX_LOGO].height, WHITE);
            break;
          case SCREEN_GAME:
            DrawText("We are drawing only one texture from various images composed!", 240, 350, 10, DARKGRAY);
            break;
      }
    
      EndDrawing();
}

void spin (int * reels) {

}