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
    for (int i = 0; i < height; i++) {
        grid->array[i] = malloc(width * sizeof(char));
        for (int j = 0; j < width; j++) {
            grid->array[i][j] = '_';
            //wprintf(L"%d,%d = %c\n", i, j, grid->array[i][j]);
        }
    }
}