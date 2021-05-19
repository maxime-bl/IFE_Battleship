//
// Created by maxim on 15/05/2021.
//

#ifndef IFE_PROJECT_MISSILES_H
#define IFE_PROJECT_MISSILES_H

typedef struct {
    int artilleryCnt, tacticalCnt, bombCnt, singleCnt;
    int maxArtillery, maxTactical, maxBomb, maxSingle;
} Inventory;

#endif //IFE_PROJECT_MISSILES_H

void init_inventory(Inventory *inventoryToInit, int difficulty);