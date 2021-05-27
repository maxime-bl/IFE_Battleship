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

    for (int b = 0; b < 5; b++) {
        array[b].squares = malloc(array[b].size * sizeof(int));
    }

}


void reset_boats(Boat *array) {
    for (int b = 0; b < 5; b++) {
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
        wprintf(L"boat %d", i);
        int squaresTaken;

        do {
            squaresTaken = 0;
            wprintf(L"size : %d\n", array[i].size);
            //randomize orientation, row and col of the top-left square
            array[i].orientation = 104 + (rand() % 2) * 14;
            array[i].row = rand() % (10 - (array[i].orientation == 'v') * (array[i].size - 1));
            array[i].col = rand() % (10 - (array[i].orientation == 'h') * (array[i].size - 1));

            //check if squares are already used by another boat
            for (int sq = 0; sq < array[i].size; sq++) {
                int row = array[i].row + (array[i].orientation == 'v') * sq;
                int col = array[i].col + (array[i].orientation == 'h') * sq;

                if (tempGrid[row][col]) {
                    squaresTaken++;
                }
            }
        } while (squaresTaken);


        //if the boat fits, reserve its squares
        for (int sq = 0; sq < array[i].size; sq++) {
            int row = array[i].row + (array[i].orientation == 'v') * sq;
            int col = array[i].col + (array[i].orientation == 'h') * sq;

            tempGrid[row][col] = 1;
        }
    }
}


int is_alive(Boat boat) {
    int health = 0;

    for (int i = 0; i < boat.size; i++) {
        if (boat.squares[i] > 0) {
            health++;
        }
    }

    if (health) {
        return 1;
    } else {
        return 0;
    }
}