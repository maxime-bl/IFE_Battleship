#ifndef IFE_PROJECT_GRID_H
#define IFE_PROJECT_GRID_H

typedef struct {
    int height, width;
    char **array;
} Grid;


/* Sets the given grid width and height, and allocate memory for its array
 * - Grid *grid : the grid to initialize
 * - int width : width of the grid in squares
 * - int height : height of the grid in squares */
void init_grid(Grid *gridToInit, int width, int height);


/* Sets all of the squares in the grid to '_'
 * - Grid *grid : the grid to reset */
void reset_grid(Grid *grid);

#endif //IFE_PROJECT_GRID_H

