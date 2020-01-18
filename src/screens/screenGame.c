#include "../include/screens.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>

void game_update(Game * game) {
    if ( (game->balance > 0) && ((int) GetTime() % 2 == 0) ) {
        game->backgroundOn = 1;
    } else {
        game->backgroundOn = 0;
    }
    
}

void game_draw(Game * game) {
    char balance[64] = {0};
    char bet[64] = {0};

    if (game->backgroundOn) {
        DrawTexture(Images[GFX_BACKGROUND_ON], 0, 0, WHITE);
    } else {
        DrawTexture(Images[GFX_BACKGROUND_OFF], 0, 0, WHITE);
    }
    sprintf(balance, "%d RON", game->balance);
    sprintf(bet, "%d RON", game->bet * game->lines);
    Vector2 balancePos = {390 - (strlen(balance) - 5) * 12, 35};
    Vector2 betPos = {830 - (strlen(bet) - 5) * 12, 35};
   
    DrawTextEx(Fonts[FONT_GANGSTER], balance, balancePos, 32, 2, WHITE);
    DrawTextEx(Fonts[FONT_GANGSTER], bet, betPos, 32, 2, YELLOW);
}