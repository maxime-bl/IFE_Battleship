//
// Created by maxim on 12/05/2021.
//

#include <malloc.h>
#include "../header/Grid.h"

void init_grid(Grid grid, int width, int height){
    grid.array = malloc(sizeof(char[width][height]));
    grid.array[0][1] = 'a';

}