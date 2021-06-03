//
// Created by maxim on 06/05/2021.
//

#ifndef IFE_PROJECT_DISPLAY_H
#define IFE_PROJECT_DISPLAY_H

#include "Missiles.h"
#include "Boats.h"

// window IDs
#define GAME_WINDOW 3
#define VICTORY_WINDOW 4
#define DEFEAT_WINDOW 5

void show_main_menu();

void show_grid(Grid grid, Boat *boatArray, Inventory inventory, int gameMode, int boatHitCnt, int boatDestroyedCnt, int boatMoved);

int init_display();

void display_window(int windowID, Grid grid, Boat *boatArray, Inventory inventory, int gameMode, int boatHitCnt,
                    int boatDestroyedCnt, int boatMoved);

#endif //IFE_PROJECT_DISPLAY_H
