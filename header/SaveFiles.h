#ifndef IFE_PROJECT_SAVEFILES_H
#define IFE_PROJECT_SAVEFILES_H

#include "Boats.h"
#include "Missiles.h"

/* Saves the game data in a text file
 * - int difficulty : difficulty of the game (1=easy, 2=medium, 3=difficult)
 * - int gameMode : the game mode (1=easy, 2=medium, 3=difficult)
 * - int turnCnt : the number of turns played
 * - int boatsHit : the number of boats hit last turn
 * - int boatsDestroyed : the number of boats destroyed last turn
 * - Grid grid : the grid of the game
 * - Inventory inv : the structure which contains the ammunition left for each missile
 * - Boat *boatArray : the array which contains all the boats
 * - int boatMoved : the variable that indicates whether a boat moved after the last turn or not
 * Returns the error code 5 (SAVING_ERROR) if it couldn't save the game
 * Returns 0 otherwise */
int save_file(int difficulty, int gameMode, int turnCnt, int boatsHit, int boatsDestroyed, Grid grid, Inventory inv,
               Boat *boatArray, int boatMoved);


 /* Loads the data from a previous game saved in a text file
 * - int *difficulty : pointer to difficulty of the game (1=easy, 2=medium, 3=difficult)
 * - int *gameMode : pointer to the game mode (1=easy, 2=medium, 3=difficult)
 * - int *turnCnt : pointer to the number of turns played
 * - int *boatsHit : pointer to the number of boats hit last turn
 * - int *boatsDestroyed : pointer to the number of boats destroyed last turn
 * - Grid *grid : pointer to the grid of the game
 * - Inventory *inv : pointer to the structure which contains the ammunition left for each missile
 * - Boat *boatArray : the array which contains all the boats
 * - int *boatMoved : pointer to the variable that indicates whether a boat moved after the last turn or not
 * Returns the error code 6 (NO_SAVEFILE) if it couldn't find a save file
 * Returns 0 otherwise */
int load_file(int *difficulty, int *gameMode, int *turnCnt, int *boatsHit, int *boatsDestroyed, Grid *grid, Inventory *inv,
               Boat *boatArray, int *boatMoved);

#endif //IFE_PROJECT_SAVEFILES_H

