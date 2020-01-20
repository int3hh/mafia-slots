#ifndef SCREENS_H
#define SCREENS_H

#define SPACER_H 5
#define SPACER_W 10

#include "game.h"

typedef struct SuitCase {
    int x;
    int y;
    int type;
    unsigned int value;
    int status;
} SuitCase;

void game_update(Game * game);
void game_draw(Game * game);

void bonus_update(Game * game);
void bonus_draw(Game * game);
void bonus_stage(Game * game);

#endif