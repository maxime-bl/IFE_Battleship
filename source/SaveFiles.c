//
// Created by maxim on 06/05/2021.
//

#include "../header/SaveFiles.h"
#include <stdio.h>
#include <stdlib.h>

void savefile() {

    FILE* gamesave;
    gamesave = fopen(".txt","w");

    if (gamesave != NULL){



        fclose(gamesave);
    }
    else{
        printf("Error: the file cannot be loaded \n");
    }

}

void loadfile() {

    FILE* gamesave;
    gamesave = fopen(".txt","r");

    if (gamesave != NULL){



        fclose(gamesave);
    }
    else{
        printf("Error: the file cannot be loaded \n");
    }

}