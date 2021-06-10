#include <stdio.h>
#include "../header/Missiles.h"
#include "../header/Grid.h"
#include "../header/Boats.h"

void init_inventory(Inventory *inventory, int diff) {
    switch (diff) {
        case 1: // easy
            inventory->maxArtillery = 3;
            inventory->maxBomb = 4;
            inventory->maxTactical = 6;
            inventory->maxSingle = 10;
            break;

        case 2: // medium
            inventory->maxArtillery = 2;
            inventory->maxBomb = 3;
            inventory->maxTactical = 5;
            inventory->maxSingle = 10;
            break;

        case 3:
            inventory->maxArtillery = 1;
            inventory->maxBomb = 2;
            inventory->maxTactical = 4;
            inventory->maxSingle = 15;
            break;
    }

    inventory->artilleryCnt = inventory->maxArtillery;
    inventory->bombCnt = inventory->maxBomb;
    inventory->tacticalCnt = inventory->maxTactical;
    inventory->singleCnt = inventory->maxSingle;
}

/* Checks if there is a boat on the square at the coordinates given
 * Sets the state of the boat's square to 0 if it his it
 * Update the grid according to the game mode
 * - int row : the row of the square to hit
 * - int col : the col of the square to hit
 * - Grid *grid : the grid to update
 * - Boat *boatArray : the array which contains all the boats
 * - int gameMode : the game mode (1=easy, 2=medium, 3=difficult)
 * - int squaresHit[5] : an array to keep track of the number of squares hit for each bot */
void hit_square(int row, int col, Grid *grid, Boat *boatArray, int gameMode, int squaresHit[5]) {
    if (row >= 0 && col >= 0 && row < grid->height && col < grid->width) {
        int isSquareEmpty = 1;
        for (int b = 0; b < 5; b++) {
            //for each boat
            for (int sq = 0; sq < boatArray[b].size; sq++) {
                //for each square of the boat
                int sqRow = boatArray[b].row + (boatArray[b].orientation == 'v') * sq;
                int sqCol = boatArray[b].col + (boatArray[b].orientation == 'h') * sq;

                if (row == sqRow && col == sqCol) { //if the square of the boat is at the coordinates
                    isSquareEmpty = 0;
                    if (boatArray[b].squares[sq]) { //square was not hit yet
                        grid->array[sqRow][sqCol] = 'X';
                        boatArray[b].squares[sq] = 0;
                        squaresHit[b]++;
                    } else if (gameMode > 1) {
                        grid->array[sqRow][sqCol] = 'x';
                    }
                }
            }
        }
        if (isSquareEmpty) {
            grid->array[row][col] = 'O';
        }
    }
}


void update_hit_counter(int *hitCnt, int *destroyedCnt, int *squaresHit, Boat *boatArray) {
    for (int b = 0; b < 5; b++) {
        if (squaresHit[b] > 0) {
            if (is_alive(boatArray[b])) {
                *hitCnt += 1;
            } else {
                *destroyedCnt += 1;
            }
        }
    }
}


void fire_artillery(Grid *grid, Boat *boatArray, int missileRow, int missileCol, int *hitCnt, int *destroyedCnt,
                    Inventory *inv, int gameMode) {

    inv->artilleryCnt--;
    int squaresHit[5] = {0, 0, 0, 0, 0};

    //check every square in the row of the missile
    int row = missileRow;
    for (int col = 0; col < grid->width; col++) {
        //for each square of the row
        hit_square(row, col, grid, boatArray, gameMode, squaresHit);
    }

    int col = missileCol;
    for (int row = 0; row < grid->width; row++) {
        //for each square of the col
        if (row != missileRow) {
            hit_square(row, col, grid, boatArray, gameMode, squaresHit);
        }
    }

    //set hitCnt and destroyedCnt
    *hitCnt = 0;
    *destroyedCnt = 0;

    update_hit_counter(hitCnt, destroyedCnt, squaresHit, boatArray);

}


void fire_tactical(Grid *grid, Boat *boatArray, int missileRow, int missileCol, int *hitCnt, int *destroyedCnt,
                   Inventory *inv, int gameMode) {
    inv->tacticalCnt--;
    int squaresHit[5] = {0, 0, 0, 0, 0};

    int isSquareEmpty = 1;
    for (int b = 0; b < 5; b++) {
        //for each boat
        for (int sq = 0; sq < boatArray[b].size; sq++) {
            //for each square of the boat
            int sqRow = boatArray[b].row + (boatArray[b].orientation == 'v') * sq;
            int sqCol = boatArray[b].col + (boatArray[b].orientation == 'h') * sq;

            if (missileRow == sqRow && missileCol == sqCol) {
                //if the tactical missile hits the boat
                isSquareEmpty = 0;

                //hit all the squares of the boat
                for (int square = 0; square < boatArray[b].size; square++) {
                    int squareRow = boatArray[b].row + (boatArray[b].orientation == 'v') * square;
                    int squareCol = boatArray[b].col + (boatArray[b].orientation == 'h') * square;
                    wprintf(L"%d %d\n", squareRow, squareCol);
                    hit_square(squareRow, squareCol, grid, boatArray, gameMode, squaresHit);
                }
            }
        }
    }

    *hitCnt = 0;
    *destroyedCnt = 0;

    update_hit_counter(hitCnt, destroyedCnt, squaresHit, boatArray);

    if (isSquareEmpty) {
        grid->array[missileRow][missileCol] = 'O';
    }
}


void fire_bomb(Grid *grid, Boat *boatArray, int missileRow, int missileCol, int *hitCnt, int *destroyedCnt,
               Inventory *inv, int gameMode) {
    inv->bombCnt--;
    int squaresHit[5] = {0, 0, 0, 0, 0};

    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {
            hit_square(missileRow + r, missileCol + c, grid, boatArray, gameMode, squaresHit);
        }
    }

    hit_square(missileRow - 2, missileCol, grid, boatArray, gameMode, squaresHit);
    hit_square(missileRow + 2, missileCol, grid, boatArray, gameMode, squaresHit);
    hit_square(missileRow, missileCol - 2, grid, boatArray, gameMode, squaresHit);
    hit_square(missileRow, missileCol + 2, grid, boatArray, gameMode, squaresHit);

    *hitCnt = 0;
    *destroyedCnt = 0;

    update_hit_counter(hitCnt, destroyedCnt, squaresHit, boatArray);
}


void fire_single(Grid *grid, Boat *boatArray, int missileRow, int missileCol, int *hitCnt, int *destroyedCnt,
                 Inventory *inv, int gameMode) {
    inv->singleCnt--;
    int squaresHit[5] = {0, 0, 0, 0, 0};

    hit_square(missileRow, missileCol, grid, boatArray, gameMode, squaresHit);

    *hitCnt = 0;
    *destroyedCnt = 0;

    update_hit_counter(hitCnt, destroyedCnt, squaresHit, boatArray);
}