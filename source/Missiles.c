//
// Created by maxim on 15/05/2021.
//

#include "../header/Missiles.h"
#include "../header/Grid.h"
#include "../header/Boats.h"

void init_inventory(Inventory *inventory, int diff) {
    switch (diff) {
        case 1: // easy
            inventory->maxArtillery = 10;
            inventory->maxBomb = 10;
            inventory->maxTactical = 10;
            inventory->maxSingle = 10;
            break;

        case 2: // medium
            inventory->maxArtillery = 3;
            inventory->maxBomb = 5;
            inventory->maxTactical = 5;
            inventory->maxSingle = 10;
            break;

        case 3: // difficult
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


void hit_square(int row, int col) {

}


void fire_artillery(Grid *grid, Boat *boatArray, int missileRow, int missileCol, int *hitCnt, int *destroyedCnt,
                    Inventory *inv, int gameMode) {

    inv->artilleryCnt--;
    int squaresHit[5] = {0, 0, 0, 0, 0};

    //check every square in the row of the missile
    int row = missileRow;
    for (int col = 0; col < grid->width; col++) {
        //for each square of the row
        int isSquareEmpty = 1;
        for (int b = 0; b < 5; b++) {
            //for each boat
            for (int sq = 0; sq < boatArray[b].size; sq++) {
                //for each square of the boat
                int sqRow = boatArray[b].row + (boatArray[b].orientation == 'h') * sq;
                int sqCol = boatArray[b].col + (boatArray[b].orientation == 'v') * sq;

                if (row == sqRow && col == sqCol) { //if the square of the boat is at the coordinates
                    isSquareEmpty = 0;
                    if (boatArray[b].squares[sq]) { //square was not hit yet
                        grid->array[sqRow][sqCol] = 'X';
                        boatArray[b].squares[sq] = 0;
                        squaresHit[b]++;
                    }
                }
            }
        }
        if (isSquareEmpty && gameMode == 1) {
            grid->array[row][col] = 'O';
        }
    }

    int col = missileCol;
    for (int row = 0; row < grid->width; row++) {
        //for each square of the col
        if (row != missileRow) {
            int isSquareEmpty = 1;
            for (int b = 0; b < 5; b++) {
                //for each boat
                if (is_alive(boatArray[b])) { //if the boat has at least one square that is not hit yet
                    for (int sq = 0; sq < boatArray[b].size; sq++) {
                        //for each square of the boat
                        int sqRow = boatArray[b].row + (boatArray[b].orientation == 'h') * sq;
                        int sqCol = boatArray[b].col + (boatArray[b].orientation == 'v') * sq;

                        if (row == sqRow && col == sqCol) { // if the square of the boat is at the coordinates
                            isSquareEmpty = 0;
                            if (boatArray[b].squares[sq]) { //square was not hit yet
                                grid->array[sqRow][sqCol] = 'X';
                                boatArray[b].squares[sq] = 0;
                                squaresHit[b]++;
                            }
                        }
                    }
                }
            }
            if (isSquareEmpty && gameMode == 1) {
                grid->array[row][col] = 'O';
            }
        }
    }

    //set hitCnt and destroyedCnt
    *hitCnt = 0;
    *destroyedCnt = 0;

    for (int b = 0; b < 5; b++) {
        if (squaresHit[b]) {
            if (is_alive(boatArray[b])) {
                *hitCnt++;
            } else {
                *destroyedCnt++;
            }
        }
    }
}


void fire_tactical(Grid *grid, Boat *boatArray, int row, int col, int *hitCnt, int *destroyedCnt, Inventory *inv) {

}


void fire_bomb(Grid *grid, Boat *boatArray, int row, int col, int *hitCnt, int *destroyedCnt, Inventory *inv) {

}


void fire_single(Grid *grid, Boat *boatArray, int row, int col, int *hitCnt, int *destroyedCnt, Inventory *inv) {

}