//
// Created by maxim on 14/05/2021.
//
#include "Grid.h"

#ifndef IFE_PROJECT_BOATS_H
#define IFE_PROJECT_BOATS_H

typedef struct {
    int row, col;
    int size;
    char orientation;
    int *squares;
} Boat;

void init_boats(Boat *boatArray);

void reset_boats(Boat *boatArray);

void place_boats(Boat *boatArray, Grid grid);

int is_alive(Boat boat);

#endif //IFE_PROJECT_BOATS_H


