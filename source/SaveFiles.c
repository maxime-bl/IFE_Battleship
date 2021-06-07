//
// Created by maxim on 06/05/2021.
//

#include "../header/SaveFiles.h"
#include "../header/Boats.h"
#include "../header/Missiles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/Dialogs.h"


// Save the game data in a text file
int save_file(int diff, int gameMode, int turnCnt, int boatsHit, int boatsDestroyed, Grid grid, Inventory inv,
               Boat *boatArray, int boatMoved) {
    FILE *gamesave;
    gamesave = fopen("savefile.txt", "w");
    if (gamesave != NULL) {
        fprintf(gamesave, "%d;%d;%d;%d;%d;%d\n", diff, gameMode, turnCnt, boatsHit, boatsDestroyed, boatMoved);
        fprintf(gamesave, "%d;%d;%d;%d\n", inv.artilleryCnt, inv.tacticalCnt, inv.bombCnt, inv.singleCnt);

        for (int row = 0; row < grid.height; row++) {
            for (int col = 0; col < grid.width - 1; col++) {
                fprintf(gamesave, "%c;", grid.array[row][col]);

            }
            fprintf(gamesave, "%c\n", grid.array[row][grid.width - 1]);
        }

        //print boats data in the file
        for (int b = 0; b < 5; b++) {
            fprintf(gamesave, "%d;%d;%d;%c;", boatArray[b].row, boatArray[b].size, boatArray[b].size,
                    boatArray[b].orientation);
            for (int sq = 0; sq < boatArray[b].size - 1; sq++) {
                fprintf(gamesave, "%d;", boatArray[b].squares[sq]);
            }
            fprintf(gamesave, "%d\n", boatArray[b].squares[boatArray[b].size - 1]);
        }


        fclose(gamesave);
    } else {
        return SAVING_ERROR;
    }

}

// Load last game data from the file
int load_file(int *difficulty, int *gameMode, int *turnCnt, int *boatsHit, int *boatsDestroyed, Grid *grid,
              Inventory *inv, Boat *boatArray, int *boatMoved) {

    FILE *gamesave;
    gamesave = fopen("savefile.txt", "r");

    if (gamesave != NULL) {
        char buffer[25];

        fscanf(gamesave, "%d;%d;%d;%d;%d;%d\n", difficulty, gameMode, turnCnt, boatsHit, boatsDestroyed, boatMoved);
        init_inventory(inv, *difficulty);
        fscanf(gamesave, "%d;%d;%d;%d\n", &inv->artilleryCnt, &inv->tacticalCnt, &inv->bombCnt, &inv->singleCnt);

        for (int row = 0; row < grid->height; row++) {
            fgets(buffer, 26, gamesave);
            for (int col = 0; col < grid->width; col++) {
                grid->array[row][col] = buffer[2 * col];
            }
        }

        for (int b = 0; b < 5; b++) {
            fscanf(gamesave, "%d;%d;%d;%c;%d;%d;%d;%d;%d\n", &boatArray[b].row, &boatArray[b].col, &boatArray[b].size,
                   &boatArray[b].orientation, &boatArray[b].squares[0], &boatArray[b].squares[1],
                   &boatArray[b].squares[2],
                   &boatArray[b].squares[3], &boatArray[b].squares[4]);
        }

        fclose(gamesave);
        return 0;

    } else {
        return NO_SAVEFILE;
    }

}