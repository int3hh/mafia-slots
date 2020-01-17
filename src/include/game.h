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
    int showLines;
    int reels[10][5];
} Game;

enum SOUNDS {S_BACKGROUND, S_SPIN, S_END};
enum GFX {GFX_LOGO, GFX_END};
enum CARDS {CARD_Q, CARD_A, CARD_K, CARD_J, CARD_BOMB, CARD_MONEY, CARD_GANGSTER, CARD_JOKER, CARD_END};
enum SCREENS {SCREEN_SPLASH, SCREEN_GAME};

extern Texture2D Images[GFX_END];

void update_game (Game * game);
void draw_game (Game game);
void load_assets();

#endif