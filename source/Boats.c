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
    // initializes temporary grid
    int tempGrid[grid.height][grid.width];
    for (int row = 0; row < grid.height; row++) {
        for (int col = 0; col < grid.width; col++) {
            tempGrid[row][col] = 0;
        }
    }

    // Placing the boats
    for (int i = 0; i < 5; i++) {
        int squaresTaken;

        do { // tries to place the boat in a random position while the previous one was occupied
            squaresTaken = 0;
            //randomize orientation, row and col of the top-left square
            array[i].orientation = 104 + (rand() % 2) * 14;
            array[i].row = rand() % (10 - (array[i].orientation == 'v') * (array[i].size - 1));
            array[i].col = rand() % (10 - (array[i].orientation == 'h') * (array[i].size - 1));

            //checks if squares are already used by another boat
            for (int sq = 0; sq < array[i].size; sq++) {
                // calculates the coordinates of the square
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

    // Counts the number of squares alive
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


void move_a_boat(Boat *boats, int diff, Grid grid) {
    // pick an alive boat randomly
    int index;
    do {
        index = rand() % 5;
    } while (is_alive((boats[index])) == 0);

    // create a temporary grid with all other boats
    int tempGrid[grid.height][grid.width];
    for (int row = 0; row < grid.height; row++) {
        for (int col = 0; col < grid.width; col++) {
            tempGrid[row][col] = 0;
        }
    }
    for (int b = 0; b < 5; b++) {
        if (b != index) {
            for (int sq = 0; sq < boats[b].size; sq++) {
                int row = boats[b].row + (boats[b].orientation == 'v') * sq;
                int col = boats[b].col + (boats[b].orientation == 'h') * sq;

                tempGrid[row][col] = 1;
            }
        }
    }


    int tryCnt = 0, squaresTaken;
    int newRow, newCol;
    do { // tries to move the boat in a random direction and at random distance while the boats doesn't fit in the previous location
        squaresTaken = 0;
        // randomizes distance from 1 to 3 according to the difficulty
        int dist = (rand() % diff) + 1;
        // sets the movement randomly along the positive or negative axis
        if (rand() % 2) {
            dist = -dist;
        }
        // picks a random direction (h or v)
        char dir = 104 + (rand() % 2) * 14;

        //Calculates new coordinates
        newRow = boats[index].row + (dir == 'v') * dist;
        newCol = boats[index].col + (dir == 'h') * dist;

        // check for each square of the boat if it can fit in the new coordinates
        for (int sq = 0; sq < boats[index].size; sq++) {
            int sqRow = newRow + (boats[index].orientation == 'v') * sq;
            int sqCol = newCol + (boats[index].orientation == 'h') * sq;

            // If the square is out of the grid
            if (sqRow < 0 || sqRow > 9 || sqCol < 0 || sqCol > 9) {
                squaresTaken++;
            }
            // If the square is already taken by another boat
            if (tempGrid[sqRow][sqCol]) {
                squaresTaken++;
            }
        }

        tryCnt++;
    } while (tryCnt < 50 && squaresTaken); // Tries up to 50 times while the boat doesn't fit

    // Saves the new coordinates if the boat can fit in this location
    boats[index].row = newRow;
    boats[index].col = newCol;

}

