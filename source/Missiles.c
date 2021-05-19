//
// Created by maxim on 15/05/2021.
//

#include "../header/Missiles.h"
#include "../header/Grid.h"
#include "../header/Boats.h"

void init_inventory(Inventory *inventory, int diff) {
    switch (diff) {
        case 1: // easy
            inventory->maxArtillery = 10;
            inventory->maxBomb = 10;
            inventory->maxTactical = 10;
            inventory->maxSingle = 10;
            break;

        case 2: // medium
            inventory->maxArtillery = 3;
            inventory->maxBomb = 5;
            inventory->maxTactical = 5;
            inventory->maxSingle = 10;
            break;

        case 3: // difficult
            inventory->maxArtillery = 1;
            inventory->maxBomb = 2;
            inventory->maxTactical = 4;
            inventory->maxSingle = 15;
            break;
    }

    inventory->artilleryCnt = inventory->maxArtillery;
    inventory->bombCnt = inventory->maxBomb;
    inventory->tacticalCnt = inventory->maxTactical;
    inventory->singleCnt = inventory->maxSingle;
}


void fire_artillery(Grid *grid, Boat *boatArray, int row, int col) {
    // inv.artilleryCnt --;

    for (int b=0; b<5; b++){
        if (is_alive(boatArray[b])){
            for (int sq=0; sq<boatArray[b].size; sq++){
                int row = boatA
            }
        }
    }

}


void fire_tactical(Grid *grid, Boat *boatArray, int row, int col) {

}


void fire_bomb(Grid *grid, Boat *boatArray, int row, int col) {

}


void fire_single(Grid *grid, Boat *boatArray, int row, int col) {

}