#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../header/Dialogs.h"
#include "../header/Boats.h"
#include "../header/Grid.h"
#include "../header/Missiles.h"
#include "../header/Display.h"

int errorCode, answer, gameLoop, dialogID, windowID, difficulty, gameMode;
int missile, row, col;
int boatHitCnt, boatDestroyedCnt;
Dialog dialogArray[9];
Boat boatArray[5];
Grid grid;
Inventory inventory;


void reset() {

    windowID = MAIN_MENU;
    errorCode = 0;
    dialogID = MAIN_MENU;
    boatHitCnt = 0;
    boatDestroyedCnt = 0;

    reset_grid(&grid);
    reset_boats(boatArray);
    //place_boats(boatArray, grid);

}


void init() {

    gameLoop = 1;
    srand(time(NULL));

    init_grid(&grid, 10, 10);
    init_display();
    init_dialogs(dialogArray);
    init_boats(boatArray);

    reset();
}


void do_something(/*int *dialogID, int *windowID, int answer, int *missile, int *row, int *col*/) {
    switch (dialogID) {
        // main menu
        case MAIN_MENU:
            switch (answer) {
                case 1:
                    dialogID = DIFF_MENU;
                    windowID = DIFF_MENU;
                    break;
                case 2:
                    //LOAD THE GAME FROM FILE
                    //GO TO THE GAME WINDOW
                    //DIALOG = PLAY_OR_QUIT
                    break;
                case 3:
                    gameLoop = 0;
                    break;
            }
            break;

            // difficulty menu
        case DIFF_MENU:
            difficulty = answer;
            dialogID = GAMEMODE_MENU;
            windowID = GAMEMODE_MENU;
            init_inventory(&inventory, difficulty);
            break;

            // game mode menu
        case GAMEMODE_MENU:
            gameMode = answer;
            place_boats(boatArray, grid);
            windowID = GAME_WINDOW;
            dialogID = PLAY_OR_QUIT;
            break;

            // play or quit (in game)
        case PLAY_OR_QUIT:
            switch (answer) {
                case 1:
                    dialogID = CHOOSE_MISSILE;
                    break;
                case 2:
                    // SAVE THE GAME
                    gameLoop = 0;
                    break;
            }
            break;
        case CHOOSE_MISSILE:
            missile = answer;
            dialogID = CHOOSE_ROW;
            break;
        case CHOOSE_ROW:
            row = answer - 97;
            dialogID = CHOOSE_COLUMN;
            break;
        case CHOOSE_COLUMN:
            col = answer;
            if (gameMode > 1) {
                reset_grid(&grid);
            }


            switch (missile) {
                case 1:
                    fire_artillery(&grid, boatArray, row, col, &boatHitCnt, &boatDestroyedCnt, &inventory, gameMode);
                    break;
                case 2:
                    fire_tactical(&grid, boatArray, row, col, &boatHitCnt, &boatDestroyedCnt, &inventory, gameMode);
                    break;
                case 3:
                    fire_bomb(&grid, boatArray, row, col, &boatHitCnt, &boatDestroyedCnt, &inventory, gameMode);
                    break;
                case 4:
                    fire_single(&grid, boatArray, row, col, &boatHitCnt, &boatDestroyedCnt, &inventory, gameMode);
                    break;
            }
            dialogID = PLAY_OR_QUIT;

            // Defeat condition
            int missileCnt = 0;
            missileCnt += inventory.artilleryCnt;
            missileCnt += inventory.tacticalCnt;
            missileCnt += inventory.bombCnt;
            missileCnt += inventory.singleCnt;
            if (missileCnt == 0) {
                windowID = DEFEAT_WINDOW;
                dialogID = RESTART;
            }

            // Victory condition
            int boatsAlive = 0;
            for (int b = 0; b < 5; b++) {
                if (is_alive(boatArray[b])) {
                    boatsAlive++;
                }
            }
            if (!boatsAlive) {
                windowID = VICTORY_WINDOW;
                dialogID = RESTART;
            }

            break;
        case RESTART:
            switch (answer) {
                case 1:
                    reset();
                    break;
                case 2:
                    gameLoop = 0;
                    break;
            }
            break;

    }
}


int main() {
    init();

    while (gameLoop) {
        display_window(windowID, grid, boatArray, inventory, gameMode, boatHitCnt, boatDestroyedCnt);

        show_dialog(dialogID, errorCode, dialogArray);
        //wprintf(L"Dialog %d, window %d, last answer %d\n", dialogID, windowID, answer);
        answer = get_answer();
        //wprintf(L"%d\n", answer);
        errorCode = check_answer(answer, dialogID, inventory);

        if (!errorCode) {
            do_something(&dialogID, &windowID, answer, &missile, &row, &col);
            // change question ID
        }
    }

    free(grid.array);

    return EXIT_SUCCESS;
}
