#include "../include/screens.h"
#include "raylib.h"
#include <string.h>
#include <stdio.h>

#define MAX_BONUS 100
#define SUITCASES 5

SuitCase suits[SUITCASES] = {0}; 
int opened;


void bonus_stage(Game * game) {
     opened = 0;
     SuitCase rawSuits[SUITCASES] = {{182, 221, 0, 0, 0}, {445, 221, 1, 0, 0}, {685, 221, 0, 0, 0}, {198, 479, 0, 0, 0}, {675, 479, 0, 0, 0}} ;
     if (game->musicOn) {
        StopMusicStream(soundTrack);
        PlayMusicStream(bonusTrack);
        SetMusicVolume(bonusTrack, 0.2f);
    }

    memcpy(&suits[0], &rawSuits[0], sizeof(suits));
    unsigned int suitcases[5]; 
    int bonusCnt = 0;
    game->wonBonus = 0;
    getRandomReel(&suitcases[0]);

    if (suitcases[0] %2 == 0) {

    for (int i = 0; i < SUITCASES; i++) {
            if (bonusCnt < 2) {
                if (suitcases[i] % 2 == 0) {
                    suits[i].value = (suitcases[i] % MAX_BONUS < 5) ? 5 : suitcases[i] % MAX_BONUS;
                    bonusCnt++;
                } 
            } else {
                break;
            }
        }
    } else {
        for (int i = SUITCASES - 1; i >= 0; i--) {
            if (bonusCnt < 2) {
                if (suitcases[i] % 2 == 0) {
                    suits[i].value = (suitcases[i] % MAX_BONUS < 5) ? 5 : suitcases[i] % MAX_BONUS;
                    bonusCnt++;
                } 
            } else {
                break;
            }
        }
    }

    for (int i = 0; i < SUITCASES; i++) {
        printf("Suitcase %d : %u\n", i, suits[i].value);
    }

}

void bonus_update(Game * game) {
    int key;
    if (opened == 0) {
        key = GetKeyPressed();
        if (key >= KEY_ONE && key <= KEY_FIVE) {
            opened = key - KEY_ONE + 1;
            if (suits[opened - 1].value) {
                game->balance += suits[opened - 1].value * (game->bet * game->lines);
                if (game->sfxOn) {
                    PlaySound(Sounds[SND_MEGAWIN]);
                }
            } else {
                if (game->sfxOn) {
                    PlaySound(Sounds[SND_LOSER]);
                }
            }
        }
    } else {
        if (IsKeyPressed(KEY_SPACE)) {
            if (game->musicOn) {
                StopMusicStream(bonusTrack);
                PlayMusicStream(soundTrack);
            }
            game->screen = SCREEN_GAME;
        }
    }
}

void bonus_draw(Game * game) {
     char bno[255];

     if (opened != 0 && suits[opened - 1].value > 0) {
         DrawTexture(Images[GFX_BONUSBKGD], 0, 0, GRAY);
     } else {
         DrawTexture(Images[GFX_BONUSBKGD], 0, 0, WHITE);
     }
     

     if (game->musicOn) {
         UpdateMusicStream(bonusTrack);
     }

     if (opened == 0) {
        for (int i = 0; i < SUITCASES; i++) {
            
            memset(bno, 0, sizeof(bno));
            sprintf(bno, "%d", i + 1);
            Vector2 pos = {suits[i].x + 80, suits[i].y + 50};
            DrawText(bno, pos.x, pos.y, 48, WHITE);
            if (suits[i].type) {
                DrawTexture(Bags[SCENTER_CLOSED], suits[i].x, suits[i].y, WHITE);
            } else {
                DrawTexture(Bags[SSIDE_CLOSED], suits[i].x, suits[i].y, WHITE);
            }
        }
    } else {
        int bagType;
        if (suits[opened - 1].value  == 0) {
            for (int i = 0; i < SUITCASES; i++) {
                    if (suits[i].value == 0) {
                        bagType = (suits[i].type == 1) ? SCENTER_EMPTY : SSIDE_EMPTY;
                    } else if (suits[i].value < (MAX_BONUS / 2)) {
                        bagType = (suits[i].type == 1) ? SCENTER_MONEY : SSIDE_MONEY;
                    } else {
                        bagType = (suits[i].type == 1) ? SCENTER_GOLD : SSIDE_GOLD;
                    }
                    DrawTexture(Bags[bagType], suits[i].x, suits[i].y, (i == opened - 1) ? WHITE : GRAY);
                    if (i == opened - 1) {
                         memset(bno, 0, sizeof(bno));
                         sprintf(bno, "%d", i + 1);
                         Vector2 pos = {suits[i].x + 80, suits[i].y + 50};
                         DrawText(bno, pos.x, pos.y, 48, WHITE);
                    }
            }
        } else {
            DrawTexture(Images[GFX_MEGAWIN], 0, 0, WHITE);
            memset(bno, 0, sizeof(bno));
            sprintf(bno, "Win: %u RON", suits[opened - 1].value * (game->bet * game->lines));
            DrawText(bno, Images[GFX_MEGAWIN].width / 2 - (strlen(bno) * 15), Images[GFX_MEGAWIN].height, 72, YELLOW);
        }
    }
}

