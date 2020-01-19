#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#define SCREEN_W 1024
#define SCREEN_H 768
#define REEL_ROW 3
#define REEL_COLUMN 5
#define BONUS_CARDS 3

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
    int reels[REEL_ROW][REEL_COLUMN];
    int winings[REEL_ROW][REEL_COLUMN];
    int betMultiplier;
    float lastEvent;
} Game;

typedef struct Line {
    Vector2 position[4];
    int lines;
    Color color;
} Line;

typedef struct CardCoord {
    int row;
    int col;
} CardCoord;

enum SOUNDS {SND_BET, SND_LINE, SND_SPIN, SND_HONK, S_END};
enum GFX {GFX_LOGO, GFX_BACKGROUND_ON, GFX_BACKGROUND_OFF, GFX_MUSIC_OFF, GFX_SFX_OFF, GFX_SPIN, GFX_END};
enum CARDS {CARD_Q, CARD_A, CARD_K, CARD_J, CARD_TEN, CARD_BOMB, CARD_MONEY, CARD_BOSS, CARD_HUSTLER, CARD_RAT, CARD_SCATTER, CARD_WILD, CARD_END};
enum FONTS {FONT_GANGSTER, FONT_END};
enum SCREENS {SCREEN_SPLASH, SCREEN_GAME, SCREEN_END};

extern Texture2D Images[GFX_END];
extern Texture2D Cards[CARD_END];
extern Font Fonts[FONT_END];
extern Sound Sounds[S_END];
extern Music soundTrack;

void update_game (Game * game);
void draw_game (Game * game);
void load_assets();
void spin(Game * game);
void printReel(int reel[REEL_ROW][REEL_COLUMN]);

#endif