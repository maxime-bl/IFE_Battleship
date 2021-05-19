//
// Created by maxim on 14/05/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include "../header/Boats.h"
#include "../header/Grid.h"

void init_boats(Boat *array) {
    array[0].size = 5;
    array[1].size = 4;
    array[2].size = 3;
    array[3].size = 3;
    array[4].size = 2;

    for (int b=0; b<5; b++){
        array[b].squares = malloc(array[b].size * sizeof(int));
    }
}


void reset_boats(Boat *array){
    for (int b=0; b<5; b++){
        for (int sq = 0; sq < array[b].size; sq++) {
            array[b].squares[sq] = 1;
        }
    }
}


void place_boats(Boat *array, Grid grid) {
    // initialize temporary grid
    int tempGrid[grid.height][grid.width];
    for (int row = 0; row < grid.height; row++) {
        for (int col = 0; col < grid.width; col++) {
            tempGrid[row][col] = 0;
        }
    }

    // Try to place the boats
    for (int i = 0; i < 5; i++) {
        int squaresTaken;

        do {
            squaresTaken = 0;
            array[i].orientation = 104 + (rand() % 2) * 14;
            array[i].row = rand() % (grid.height - (array[i].orientation == 'v') * array[i].size);
            array[i].col = rand() % (grid.width - (array[i].orientation == 'h') * array[i].size);

            for (int sq = 0; sq < array[i].size; sq++) {
                if (tempGrid[array[i].row + sq * (array[i].orientation == 'v')][array[i].col +
                                                                                sq * (array[i].orientation == 'h')] >
                    0) {
                    squaresTaken++;
                }
            }
        } while (squaresTaken);

        //If the boat fits

        //wprintf(L"%d %c, %d %d\n",array[i].size,array[i].orientation, array[i].row, array[i].col);
        if (array[i].orientation == 'h') {
            for (int row = array[i].row - 1; row <= array[i].row + 1; row++) {
                for (int col = array[i].col - 1; col <= array[i].col + array[i].size; col++) {
                    if (row >= 0 && row < grid.height && col >= 0 && col < grid.width) {
                        tempGrid[row][col]++;
                    }
                }
            }
        } else {
            for (int row = array[i].row - 1; row <= array[i].row + array[i].size; row++) {
                for (int col = array[i].col - 1; col <= array[i].col + 1; col++) {
                    if (row >= 0 && row < grid.height && col >= 0 && col < grid.width) {
                        tempGrid[row][col]++;
                    }
                }
            }
        }
    }
}


int is_alive(Boat boat){
    int health=0;

    for (int i=0; i<boat.size; i++){
        if (boat.squares[i]>0){
            health++;
        }
    }

    if (health) {
        return 1;
    } else {
        return 0;
    }
}