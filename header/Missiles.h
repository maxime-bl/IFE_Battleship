#include "Grid.h"
#include "Boats.h"

#ifndef IFE_PROJECT_MISSILES_H
#define IFE_PROJECT_MISSILES_H

typedef struct {
    int artilleryCnt, tacticalCnt, bombCnt, singleCnt;
    int maxArtillery, maxTactical, maxBomb, maxSingle;
} Inventory;


/* Set the maximum number and the amount of each missile in the inventory according to the difficulty
 * - Inventory *inventoryToInit : inventory to initialize
 * - int difficulty : difficulty of the game (1=easy, 2=medium, 3=difficult) */
void init_inventory(Inventory *inventoryToInit, int difficulty);

/* Fires the artillery missile at the given coordinates
 * The function will set the value of the boats' squares hit to 0, and then update the grid according to the game mode
 * - Grid *grid : the grid to modify
 * - Boat *boatArray : the array which contains all the boats
 * - int row : the row of the square were the missile will be fired
 * - int col : the col of the square were the missile will be fired
 * - int *hitCnt : a pointer to the variable containing the number of boats hit each turn
 * - int *destroyedCnt : a pointer to the variable containing the number of boats destroyed each turn
 * - Inventory *inventory : a pointer to the inventory holding the number of missiles left
 * - int gameMode : the game mode (1=easy, 2=medium, 3=difficult)
 * The function will update hitCnt and destroyedCnt after hitting the boats */
void fire_artillery(Grid *grid, Boat *boatArray, int row, int col, int *hitCnt, int *destroyedCnt, Inventory *inventory, int gameMode);


/* Fires the tactical missile at the given coordinates
 * The function will set the value of the boats' squares hit to 0, and then update the grid according to the game mode
 * - Grid *grid : the grid to modify
 * - Boat *boatArray : the array which contains all the boats
 * - int row : the row of the square were the missile will be fired
 * - int col : the col of the square were the missile will be fired
 * - int *hitCnt : a pointer to the variable containing the number of boats hit each turn
 * - int *destroyedCnt : a pointer to the variable containing the number of boats destroyed each turn
 * - Inventory *inventory : a pointer to the inventory holding the number of missiles left
 * - int gameMode : the game mode (1=easy, 2=medium, 3=difficult)
 * The function will update hitCnt and destroyedCnt after hitting the boats */
void fire_tactical(Grid *grid, Boat *boatArray, int row, int col, int *hitCnt, int *destroyedCnt, Inventory *inventory, int gameMode);


/* Fires the bomb at the given coordinates
 * The function will set the value of the boats' squares hit to 0, and then update the grid according to the game mode
 * - Grid *grid : the grid to modify
 * - Boat *boatArray : the array which contains all the boats
 * - int row : the row of the square were the missile will be fired
 * - int col : the col of the square were the missile will be fired
 * - int *hitCnt : a pointer to the variable containing the number of boats hit each turn
 * - int *destroyedCnt : a pointer to the variable containing the number of boats destroyed each turn
 * - Inventory *inventory : a pointer to the inventory holding the number of missiles left
 * - int gameMode : the game mode (1=easy, 2=medium, 3=difficult)
 * The function will update hitCnt and destroyedCnt after hitting the boats */
void fire_bomb(Grid *grid, Boat *boatArray, int row, int col, int *hitCnt, int *destroyedCnt, Inventory *inventory, int gameMode);


/* Fires the single missile at the given coordinates
 * The function will set the value of the boats' squares hit to 0, and then update the grid according to the game mode
 * - Grid *grid : the grid to modify
 * - Boat *boatArray : the array which contains all the boats
 * - int row : the row of the square were the missile will be fired
 * - int col : the col of the square were the missile will be fired
 * - int *hitCnt : a pointer to the variable containing the number of boats hit each turn
 * - int *destroyedCnt : a pointer to the variable containing the number of boats destroyed each turn
 * - Inventory *inventory : a pointer to the inventory holding the number of missiles left
 * - int gameMode : the game mode (1=easy, 2=medium, 3=difficult)
 * The function will update hitCnt and destroyedCnt after hitting the boats */
void fire_single(Grid *grid, Boat *boatArray, int row, int col, int *hitCnt, int *destroyedCnt, Inventory *inventory, int gameMode);

#endif //IFE_PROJECT_MISSILES_H