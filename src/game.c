#include "include/game.h"
#include "raylib.h"
#include "include/screens.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef linux
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
    #include <linux/random.h>
#endif


Texture2D Images[GFX_END];
Font Fonts[FONT_END];
Sound Sounds[S_END];
Music soundTrack;
Texture2D Cards[CARD_END];

void load_assets () {

    char gfx_filez[GFX_END][255] = {"assets/images/logo.png", "assets/images/background.png", "assets/images/backgroundoff.png",
                                   "assets/images/nomusic.png", "assets/images/nosfx.png", "assets/images/spining.png"};
    char font_filez[FONT_END][255] = {"assets/fonts/gangster.ttf"};
    char soundtrack_file[255] = {"assets/sounds/soundtrack.ogg"};
    char card_filez[CARD_END][255] = {"assets/images/q_%d.png", "assets/images/a_%d.png", "assets/images/k_%d.png",
                                      "assets/images/j_%d.png", "assets/images/ten_%d.png", "assets/images/bomb_%d.png",
                                      "assets/images/money_%d.png", "assets/images/boss_%d.png", "assets/images/hustler_%d.png",
                                      "assets/images/rat_%d.png", "assets/images/scatter_%d.png", "assets/images/wild_%d.png"};
    char sound_filez[S_END][255] = {"assets/sounds/bet.ogg", "assets/sounds/glass.ogg", "assets/sounds/spin.ogg",
                                    "assets/sounds/honk.ogg"};

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

    for (int i = 0; i < CARD_END; i++) {
        char asset[255];
        memset(asset, 0, sizeof(asset));
        sprintf(asset, card_filez[i], 0);
        Cards[i] = LoadTexture(asset);
    }

    for (int i = 0; i < S_END; i++) {
        Sounds[i] = LoadSound(sound_filez[i]);
    }
}

void update_game (Game * game) {

    if (IsKeyPressed(KEY_S)) {
        game->musicOn = !game->musicOn;
        if (!game->musicOn) {
            StopMusicStream(soundTrack);
        } else {
            PlayMusicStream(soundTrack);
        }
    } else {
         if (game->musicOn) {
            UpdateMusicStream(soundTrack);
        }
    }

    if (IsKeyPressed(KEY_X)) {
        game->sfxOn = !game->sfxOn;
    }

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

    if (!game->sfxOn) {
        DrawTexture(Images[GFX_SFX_OFF], 40, SCREEN_H - 50, WHITE);
    }

    if (!game->musicOn) {
        DrawTexture(Images[GFX_MUSIC_OFF], 80, SCREEN_H - 50, WHITE);
    }

    
      EndDrawing();
}

void spin (Game * game) {
    unsigned int reel[5];
    int seeded = 0;
    #ifdef linux
        int c;
        int fd = open("/dev/urandom", O_RDONLY);
        if ( fd != -1 ) {
            if ( ioctl(fd, RNDGETENTCNT, &c) == 0 && c > 160 ) {
                  read(fd, &reel, sizeof(reel));
                  seeded = 1;
            }
            close(fd);
        } 
    #endif
    if (!seeded) {
        printf("FATAL: Not enough randomness!");
        exit(1);
    }
    for (int i = 0; i < 5; i++) {
        reel[i] %= (CARD_END);
    }
    memcpy(&game->reels[2], &game->reels[1], sizeof(game->reels[1]));
    memcpy(&game->reels[1], &game->reels[0], sizeof(game->reels[0]));
    memcpy(&game->reels[0], &reel[0], sizeof(reel));
    
   //  printReel(game->reels);
}

void printReel(int reel[REEL_ROW][REEL_COLUMN]) {
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d\t", reel[i][j]);
        }
        printf("\n\n");
    }
    printf("-----------------------------------------------------\n\n");
}