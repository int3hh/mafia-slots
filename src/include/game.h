#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#define SCREEN_W 1024
#define SCREEN_H 768
#define REEL_ROW 3
#define REEL_COLUMN 5
#define BONUS_CARDS 3
#define MAX_CARDS 24
#define LID_STATES_MAX 10

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
    int wonBonus;
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

enum SOUNDS {SND_BET, SND_LINE, SND_SPIN, SND_HONK, SND_WIN, SND_BONUS, SND_MEGAWIN, SND_LOSER, S_END};
enum GFX {GFX_LOGO, GFX_BACKGROUND_ON, GFX_BACKGROUND_OFF, GFX_MUSIC_OFF, GFX_SFX_OFF, GFX_SPIN, GFX_BONUS, GFX_BONUSBKGD, GFX_MEGAWIN, GFX_END};
enum CARDS {CARD_Q, CARD_A, CARD_K, CARD_J, CARD_TEN, CARD_BOMB, CARD_MONEY, CARD_BOSS, CARD_HUSTLER, CARD_RAT, CARD_SCATTER, CARD_WILD, CARD_END};
enum FONTS {FONT_GANGSTER, FONT_END};
enum SCREENS {SCREEN_SPLASH, SCREEN_GAME, SCREEN_BONUS, SCREEN_END};
enum SUITCASES {SCENTER_CLOSED, SSIDE_CLOSED, SCENTER_EMPTY, SCENTER_GOLD, SCENTER_MONEY, SSIDE_EMPTY, SSIDE_GOLD, SSIDE_MONEY, SCENTER_LID, SSIDE_LID, SUITCASES_END}; 

extern Texture2D Images[GFX_END];
extern Texture2D Cards[CARD_END][24];
extern Texture2D Bags[SUITCASES_END];

extern Font Fonts[FONT_END];
extern Sound Sounds[S_END];
extern Music soundTrack;
extern Music bonusTrack;

void update_game (Game * game);
void draw_game (Game * game);
void load_assets();
void spin(Game * game);
void printReel(int reel[REEL_ROW][REEL_COLUMN]);
int getRandomReel(unsigned int * reel);

#endif