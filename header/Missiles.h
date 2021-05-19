//
// Created by maxim on 15/05/2021.
//

#include "Grid.h"
#include "Boats.h"

#ifndef IFE_PROJECT_MISSILES_H
#define IFE_PROJECT_MISSILES_H

typedef struct {
    int artilleryCnt, tacticalCnt, bombCnt, singleCnt;
    int maxArtillery, maxTactical, maxBomb, maxSingle;
} Inventory;

void init_inventory(Inventory *inventoryToInit, int difficulty);

void fire_artillery(Grid *grid, Boat *boatArray, int row, int col);

void fire_tactical(Grid *grid, Boat *boatArray, int row, int col);

void fire_bomb(Grid *grid, Boat *boatArray, int row, int col);

void fire_single(Grid *grid, Boat *boatArray, int row, int col);

#endif //IFE_PROJECT_MISSILES_H