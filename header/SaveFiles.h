//
// Created by maxim on 06/05/2021.
//

#ifndef IFE_PROJECT_SAVEFILES_H
#define IFE_PROJECT_SAVEFILES_H

#include "Boats.h"
#include "Missiles.h"

void save_file(int difficulty, int gameMode, int turnCnt, int boatsHit, int boatsDestroyed, Grid grid, Inventory inv,
               Boat *boatArray, int boatMoved);

int load_file(int *difficulty, int *gameMode, int *turnCnt, int *boatsHit, int *boatsDestroyed, Grid *grid, Inventory *inv,
               Boat *boatArray, int *boatMoved);

#endif //IFE_PROJECT_SAVEFILES_H

