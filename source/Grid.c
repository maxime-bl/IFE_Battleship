//
// Created by maxim on 12/05/2021.
//

#include <malloc.h>
#include <stdio.h>
#include "../header/Grid.h"

void init_grid(Grid *grid, int width, int height) {
    grid->width = width;
    grid->height = height;

    // Allocate the memory for the array and initialize the values
    grid->array = malloc(height * sizeof(char *));
    for (int row = 0; row < height; row++) {
        grid->array[row] = malloc(width * sizeof(char));
    }

    reset_grid(grid);
}

void reset_grid(Grid *grid){
    for (int row = 0; row < grid->height; row++) {
        grid->array[row] = malloc(grid->width * sizeof(char));
        for (int col = 0; col < grid->width; col++) {
            grid->array[row][col] = '_';
        }
    }
}