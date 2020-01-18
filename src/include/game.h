#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#define SCREEN_W 1024
#define SCREEN_H 768


typedef struct Game {
    int balance;
    int lines;
    int bet;
    int screen;
    int spining;
    int sfxOn;
    int musicOn;
    int showLines;
    int backgroundOn;
    int reels[10][5];
    float lastEvent;
} Game;

enum SOUNDS {S_SOUNDTRACK, S_END};
enum GFX {GFX_LOGO, GFX_BACKGROUND_ON, GFX_BACKGROUND_OFF, GFX_END};
enum CARDS {CARD_Q, CARD_A, CARD_K, CARD_J, CARD_BOMB, CARD_MONEY, CARD_GANGSTER, CARD_JOKER, CARD_END};
enum FONTS {FONT_GANGSTER, FONT_END};
enum SCREENS {SCREEN_SPLASH, SCREEN_GAME, SCREEN_END};

extern Texture2D Images[GFX_END];
extern Font Fonts[FONT_END];
extern Sound Sounds[S_END];
extern Music soundTrack;

void update_game (Game * game);
void draw_game (Game * game);
void load_assets();

#endif