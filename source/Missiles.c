//
// Created by maxim on 15/05/2021.
//

#include "../header/Missiles.h"

void init_inventory(Inventory *inventory, int diff) {
    switch (diff) {
        // easy
        case 1:
            inventory->maxArtillery = 10;
            inventory->maxBomb = 10;
            inventory->maxTactical = 10;
            inventory->maxSingle = 10;
            break;

            // medium
        case 2:
            inventory->maxArtillery = 3;
            inventory->maxBomb = 5;
            inventory->maxTactical = 5;
            inventory->maxSingle = 10;
            break;

            // difficult
        case 3:
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