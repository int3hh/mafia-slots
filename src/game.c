#include "include/game.h"
#include "raylib.h"
#include "include/screens.h"

Texture2D Images[GFX_END];
Font Fonts[FONT_END];
Sound Sounds[S_END];
Music soundTrack;

void load_assets () {

    char gfx_filez[GFX_END][255] = {"assets/images/logo.png", "assets/images/background.png", "assets/images/background_off.png"};
    char font_filez[FONT_END][255] = {"assets/fonts/gangster.ttf"};
    char soundtrack_file[255] = {"assets/sounds/soundtrack.ogg"};
    char sound_filez[S_END][255] = {};

    // Loading graphics 
    for (int i = 0; i < GFX_END; i++) {
        Images[i] = LoadTexture(gfx_filez[i]);
    }

    for (int i = 0; i < FONT_END; i++) {
        Fonts[i] = LoadFont(font_filez[i]);
    }

    soundTrack = LoadMusicStream(soundtrack_file);
    SetMusicVolume(soundTrack, 0.1f);
    PlayMusicStream(soundTrack);

 /*   for (int i = 0; i < S_END; i++) {
        Sounds[i] = LoadSound(sound_filez[i]);
    }
*/
}

void update_game (Game * game) {
    switch (game->screen)
    {
    case SCREEN_SPLASH:
        if (GetTime() > 3) {
            game->screen = SCREEN_GAME;
            game->spining = -1;
        }
        break;
    case SCREEN_GAME:
        game_update(game);
        break;

    default:
        break;
    }
}

void draw_game (Game * game) {
      BeginDrawing();

      switch (game->screen) {
          case SCREEN_SPLASH:
            if (game->spining == -1) {
                ClearBackground(BLACK);
                DrawTexture(Images[GFX_LOGO], SCREEN_W / 2 - (Images[GFX_LOGO].height*2)  , SCREEN_H / 2 - Images[GFX_LOGO].height, WHITE);
                game->spining = 0;
            }
            break;
          case SCREEN_GAME:
            if (game->spining == -1) {
                ClearBackground(BLACK);
                game->spining = 0;
            } else {
               game_draw(game);
            }
            break;
      }
    
      EndDrawing();
}

void spin (int * reels) {

}