#include "../include/screens.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>

Line lines[5] = { { { {147, 350}, {873, 350} }, 1, PINK }, { { {147, 195}, {873, 195} }, 1, RED },
                  { { {147, 515}, {873, 515} }, 1, LIME }, { { {168, 105}, {508, 506}, {508, 506}, {858, 108}}, 2, VIOLET}, 
                  { { {167, 591}, {507, 197}, {507, 197}, {848, 596}}, 2, SKYBLUE } };

int multipliers[CARD_END] = {1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 0, 2 };

int check_line(int line, Game * game) {
  //  int defa[5] = {CARD_HUSTLER, CARD_HUSTLER,CARD_Q, CARD_Q, CARD_Q};
  // memcpy(&game->reels[line][0], &defa[0], sizeof(defa));
    int symbol = -1, start = 0, len = 1;

    for (int i = 0; i < REEL_COLUMN; i++) {
        if ( (symbol != game->reels[line][i]) && (game->reels[line][i] != CARD_WILD) ) {
            if (len >= 3) {
                break;
            }
            start = i;
            len = 1;
            symbol = game->reels[line][i];
        } else {
            len++;
        }
    }
    if (len >= 3) {
        for (int j = start; j < start+len; j++) {
            game->winings[line][j] = 1;
        }
        return len;
    } 

    return 0;
   
}

int check_diag(int line, Game * game) {
    CardCoord coords [] = { {2,0}, {1,1}, {0,2}, {1,3}, {2,4} };
    
    if (line == 4) {
        CardCoord coord2 [] = { {0,0}, {1,1}, {2,2}, {1,3}, {0,4} };
        memcpy(&coords[0], &coord2[0], sizeof(coord2));
    } 
    
    int symbol = -1, start = 0, len = 1;

    for (int i = 0; i < sizeof(coords) / sizeof(CardCoord); i++) {
        if ( (symbol != game->reels[coords[i].row][coords[i].col]) && (game->reels[coords[i].row][coords[i].col] != CARD_WILD) ) {
            if (len >= 3) {
                break;
            }
            start = i;
            len = 1;
            symbol = game->reels[coords[i].row][coords[i].col];
        } else {
            len++;
        }
    }

    if (len >= 3) {
        printf(" DIAG start = %d and len = %d ---------------- \n", start, len);
      
        for (int j = start; j < (start+len); j++) {
            game->winings[coords[j].row][coords[j].col] = 1;
        }
        printReel(game->winings);
        return len;
    }

    return 0;
    
}

void check_win(Game * game) {
    memset(&game->winings[0][0], 0, sizeof(game->winings));
    int win = 0;
    win += check_line(1, game);
    if (game->lines > 1) {
        win += check_line(0, game);
    } 

    if (game->lines > 2) {
        win += check_line(2, game);
    }

    if (game->lines > 3) {
        win += check_diag(4, game);
    }

    if (game->lines > 4) {
        win += check_diag(5, game);
    }

    if (win) {
        win = 0;
        int cards = 0;
        for (int i = 0; i < REEL_ROW; i++) {
            for (int j = 0; j < REEL_COLUMN; j++) {
                if (game->winings[i][j] > 0) {
                    if (win < multipliers[game->reels[i][j]]) {
                        win = multipliers[game->reels[i][j]];
                    }
                    cards++;
                }
            }
        }
        if (cards > BONUS_CARDS) {
            win++;
            
        }
        game->betMultiplier = win;
        game->balance += (game->bet * game->lines) * game->betMultiplier;
    }

}

void game_update(Game * game) {
    if ( (game->balance > 0) && ((int) GetTime() % 2 == 0) ) {
        game->backgroundOn = 1;
    } else {
        game->backgroundOn = 0;
    }

    if (game->balance > 0) {
        if (!game->spining) {
            if (IsKeyPressed(KEY_BACKSPACE)) {
                game->showLines = 1;
                int new_bet = game->bet;
                if (new_bet == 1) {
                    new_bet = 3;
                } else if (new_bet == 3) {
                    new_bet = 5;
                } else {
                        new_bet += 5;
                        if ( (new_bet > 100) || (new_bet * game->lines > game->balance) ) {
                            new_bet = 1;
                        }
                }
                if (new_bet * game->lines > game->balance) {
                    if (game->sfxOn) {
                        PlaySound(Sounds[SND_HONK]);
                    }
                } else {
                    game->bet = new_bet;
                    if (game->sfxOn) {
                        PlaySound(Sounds[SND_BET]);
                    }
                }
            }

            if (IsKeyPressed(KEY_ENTER)) {
                game->lines += 1;
                if ( (game->lines > 5) || (game->bet * game->lines > game->balance) ){
                    game->lines = 1;
                }

                if (game->sfxOn) {
                    PlaySound(Sounds[SND_LINE]);
                }            
                game->showLines = 1;
            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            game->showLines = 0;
             if (game->spining == 0) {
                 game->betMultiplier = 0;
                if (game->balance - (game->bet * game->lines) < 0) {
                    game->showLines = 1;
                    game->lines = 1;
                    game->bet = game->balance;
                    if (game->sfxOn) {
                        PlaySound(Sounds[SND_HONK]);
                    }
                } else {
                    spin(game);
                    game->balance -= game->bet * game->lines;
                    game->spining = 1;
                    if (game->sfxOn) {
                        PlaySound(Sounds[SND_SPIN]);
                    }
                }
            } else {
                if (game->spining < 5) {
                    for (int k = 0; k < 5; k++) {
                        spin(game);
                    }
                }
                 if (game->sfxOn) {
                    StopSound(Sounds[SND_SPIN]);
                    PlaySound(Sounds[SND_LINE]);
                 }
                 game->spining = 100;
                
            }
        }
    }

    if (game->spining) {
        if (game->spining >= 100) {
            check_win(game);
            game->spining = 0;
        } else {
            game->spining += 1;
            spin(game);
        }
    }

}


void game_draw(Game * game) {
    char balance[64] = {0};
    char bet[64] = {0};
    char win[255] = {0};

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

        Vector2 initialPos = {187, 130};
        for (int i = 0; i < REEL_ROW; i++) {
            if (i) {
                initialPos.y += Cards[CARD_Q].height + SPACER_H;
            }
            for (int j = 0; j < REEL_COLUMN; j++) {
                Vector2 cardPos = {initialPos.x + (float) (j * Cards[CARD_Q].width), initialPos.y};
                if (j) {
                    cardPos.x += SPACER_W;
                }
                if (game->betMultiplier) {
                    if (game->winings[i][j] == 0) {
                        DrawTexture(Cards[game->reels[i][j]], cardPos.x, cardPos.y, GRAY);    
                    } else {
                        DrawTexture(Cards[game->reels[i][j]], cardPos.x, cardPos.y, WHITE);    
                    }
                } else {
                    DrawTexture(Cards[game->reels[i][j]], cardPos.x, cardPos.y, WHITE);
                }
                
            }
        }

    if (game->spining) {
        DrawTexture(Images[GFX_SPIN], 468, 705, WHITE);
    }

    if (game->showLines) {
        for (int i = 0; i < game->lines; i++) {
            for (int j = 0; j < lines[i].lines; j++) {
                DrawLineEx(lines[i].position[j*2], lines[i].position[j*2+1], 5, lines[i].color);
            }
        }
    }

    if (game->betMultiplier) {
        sprintf(win, "WIN! Bet X%d = %d RON", game->betMultiplier, (game->bet * game->lines) * game->betMultiplier);
        Vector2 winPos = {308, 655};
        DrawTextEx(Fonts[FONT_GANGSTER], win, winPos, 42, 2, PINK);    
    }
}