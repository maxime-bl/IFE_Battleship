#ifndef IFE_PROJECT_DISPLAY_H
#define IFE_PROJECT_DISPLAY_H

#include "Missiles.h"
#include "Boats.h"

// window IDs
#define MAIN_MENU 0
#define DIFF_MENU  1
#define GAMEMODE_MENU  2
#define GAME_WINDOW 3
#define VICTORY_WINDOW 4
#define DEFEAT_WINDOW 5


/* Sets the console mode in order to display special characters
 * Enable escape characters, which allows us to add colors to te console */
int init_display();


// Prints the main menu in the console after skipping 50 lines
void show_main_menu();


/* Prints the game window in the console, displaying the grid, the number of missiles, the health of the boats, the number
 * of boats hit and destroyed last round, and whether a boat moved last round or not.
 * - Grid grid : the grid to display
 * - Boat *boatArray : the array which contains all the boats
 * - Inventory inventory : the structure which contains the number of each missile left
 * - int gameMode : game mode (1 for Easy, 2 for Medium, 3 for Difficult)
 * - int boatHitCnt : number of boats that were hit last round
 * - int boatDestroyedCnt : number of boats that were destroyed last round
 * - int boatMoved : 1 if a boat moved last round, 0 otherwise */
void show_grid(Grid grid, Boat *boatArray, Inventory inventory, int gameMode, int boatHitCnt, int boatDestroyedCnt,
               int boatMoved);


/* Prints a window in the console according to the window IDs defined above
 * - Grid grid : the grid to display
 * - Boat *boatArray : the array which contains all the boats
 * - Inventory inventory : the structure which contains the number of each missile left
 * - int gameMode : game mode (1 for Easy, 2 for Medium, 3 for Difficult)
 * - int boatHitCnt : number of boats that were hit last round
 * - int boatDestroyedCnt : number of boats that were destroyed last round
 * - int boatMoved : 1 if a boat moved last round, 0 otherwise */
void display_window(int windowID, Grid grid, Boat *boatArray, Inventory inventory, int gameMode, int boatHitCnt,
                    int boatDestroyedCnt, int boatMoved);

#endif //IFE_PROJECT_DISPLAY_H
