//
// Created by maxim on 12/05/2021.
//

#ifndef IFE_PROJECT_GRID_H
#define IFE_PROJECT_GRID_H

typedef struct {
    int height, width;
    char **array;
} Grid;

void init_grid(Grid *gridToInit, int width, int height);

void reset_grid(Grid *grid);

#endif //IFE_PROJECT_GRID_H

