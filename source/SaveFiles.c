#include "../header/SaveFiles.h"
#include "../header/Boats.h"
#include "../header/Missiles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/Dialogs.h"



int save_file(int diff, int gameMode, int turnCnt, int boatsHit, int boatsDestroyed, Grid grid, Inventory inv,
               Boat *boatArray, int boatMoved) {
    FILE *gamesave;
    gamesave = fopen("savefile.txt", "w");
    if (gamesave != NULL) { //if the save file exists
        // Prints all the game variables and the inventory
        fprintf(gamesave, "%d;%d;%d;%d;%d;%d\n", diff, gameMode, turnCnt, boatsHit, boatsDestroyed, boatMoved);
        fprintf(gamesave, "%d;%d;%d;%d\n", inv.artilleryCnt, inv.tacticalCnt, inv.bombCnt, inv.singleCnt);

        // Prints all the squares of the grid row after row
        for (int row = 0; row < grid.height; row++) {
            for (int col = 0; col < grid.width - 1; col++) {
                fprintf(gamesave, "%c;", grid.array[row][col]);

            }
            fprintf(gamesave, "%c\n", grid.array[row][grid.width - 1]);
        }

        // Prints boats data in the file
        for (int b = 0; b < 5; b++) {
            fprintf(gamesave, "%d;%d;%d;%c;", boatArray[b].row, boatArray[b].size, boatArray[b].size,
                    boatArray[b].orientation);
            for (int sq = 0; sq < boatArray[b].size - 1; sq++) {
                fprintf(gamesave, "%d;", boatArray[b].squares[sq]);
            }
            fprintf(gamesave, "%d\n", boatArray[b].squares[boatArray[b].size - 1]);
        }


        fclose(gamesave);
        return 0;
    } else {
        return SAVING_ERROR;
    }

}


int load_file(int *difficulty, int *gameMode, int *turnCnt, int *boatsHit, int *boatsDestroyed, Grid *grid,
              Inventory *inv, Boat *boatArray, int *boatMoved) {

    FILE *gamesave;
    gamesave = fopen("savefile.txt", "r");

    if (gamesave != NULL) { // If the save file exists
        char buffer[25];

        // Loads the game variables and the inventory
        fscanf(gamesave, "%d;%d;%d;%d;%d;%d\n", difficulty, gameMode, turnCnt, boatsHit, boatsDestroyed, boatMoved);
        init_inventory(inv, *difficulty);
        fscanf(gamesave, "%d;%d;%d;%d\n", &inv->artilleryCnt, &inv->tacticalCnt, &inv->bombCnt, &inv->singleCnt);

        // Loads the grid
        for (int row = 0; row < grid->height; row++) {
            fgets(buffer, 26, gamesave);
            for (int col = 0; col < grid->width; col++) {
                grid->array[row][col] = buffer[2 * col];
            }
        }

        // Loads the boats data
        for (int b = 0; b < 5; b++) {
            fscanf(gamesave, "%d;%d;%d;%c;%d;%d;%d;%d;%d\n", &boatArray[b].row, &boatArray[b].col, &boatArray[b].size,
                   &boatArray[b].orientation, &boatArray[b].squares[0], &boatArray[b].squares[1],
                   &boatArray[b].squares[2],
                   &boatArray[b].squares[3], &boatArray[b].squares[4]);
        }

        fclose(gamesave);
        return 0;

    } else { // If there is now save file to load
        return NO_SAVEFILE;
    }

}