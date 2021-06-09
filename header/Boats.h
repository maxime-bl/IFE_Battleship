#include "Grid.h"

#ifndef IFE_PROJECT_BOATS_H
#define IFE_PROJECT_BOATS_H

typedef struct {
    int row, col;
    int size;
    char orientation;
    int *squares;
} Boat;

/* Sets the size of each boat and allocates memory for the square arrays
 * - Boat boatArray : the array which contains the boats to place */
void init_boats(Boat *boatArray);

/* Reset the square array of each boat
 * - Boat boatArray : the array which contains the boats to reset */
void reset_boats(Boat *boatArray);

/* Sets the boats coordinates and orientations randomly
 * - Boat boatArray : the array which contains the boats to place
 * - Grid grid : the grid structure used in the game */
void place_boats(Boat *boatArray, Grid grid);

/* This functions will check if the boat as at least one square that is not hit
 * - Boat boat : boat to check
 * Return 1 if the boat is still alive, 0 if all its squares are hit*/
int is_alive(Boat boat);

/* Picks one boat randomly and moves it in a random direction
 * In Easy, the boat can only move 1 square away
 * In Medium, the boat can move 1 or 2 squares away
 * In Difficult, the boat can move from 1 to 3 squares away
 * - Boat *boatArray : the array which contains all of the boats
 * - int difficulty : the difficulty of the game (1-3)
 * - Grid grid : the grid structure used in the game */
void move_a_boat(Boat *boatArray, int difficulty, Grid grid);

#endif //IFE_PROJECT_BOATS_H


