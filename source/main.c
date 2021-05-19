#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../header/Dialogs.h"
#include "../header/Boats.h"
#include "../header/Grid.h"
#include "../header/Missiles.h"
#include "../header/Display.h"

int errorCode, answer, gameLoop, dialogID, windowID, difficulty, gameMode;
Dialog dialogArray[9];
Boat boatArray[5];
Grid grid;
Inventory inventory;


void init() {
    windowID = MAIN_MENU;
    errorCode = 0;
    gameLoop = 1;
    dialogID = MAIN_MENU;
    srand(time(NULL));

    init_display();
    init_dialogs(dialogArray);
    init_grid(&grid, 10, 10);
    init_boats(boatArray);
    place_boats(boatArray, grid);
}


void do_something(int *dialogID, int *windowID, int answer) {
    switch (*dialogID) {
        // main menu
        case MAIN_MENU:
            switch (answer) {
                case 1:
                    *dialogID = DIFF_MENU;
                    *windowID = DIFF_MENU;
                    break;
                case 2:
                    //load the file and go to the game window
                    break;
                case 3:
                    gameLoop = 0;
                    break;
            }
            break;

            // difficulty menu
        case DIFF_MENU:
            difficulty = answer;
            *dialogID = GAMEMODE_MENU;
            *windowID = GAMEMODE_MENU;
            init_inventory(&inventory, difficulty);
            wprintf(L"Bombs : %d\n", inventory.bombCnt);
            break;

            // game mode menu
        case GAMEMODE_MENU:
            gameMode = answer;
            place_boats(boatArray, grid);
            *windowID = GAME_WINDOW;
            *dialogID = PLAY_OR_QUIT;
            break;

            // play or quit (in game)
        case PLAY_OR_QUIT:
            switch (answer) {
                case 1:
                    *dialogID = CHOOSE_MISSILE;
                    break;
                case 2:
                    // SAVE THE GAME
                    gameLoop = 0;
                    break;
            }
            break;
    }
}


int main() {
    init();

    while (gameLoop) {
        display_window(windowID, grid, boatArray, inventory, gameMode);

        show_dialog(dialogID, errorCode, dialogArray);
        //wprintf(L"Dialog %d, window %d, last answer %d\n", dialogID, windowID, answer);
        answer = get_answer();
        //wprintf(L"%d\n", answer);
        errorCode = check_answer(answer, dialogID);

        if (!errorCode) {
            do_something(&dialogID, &windowID, answer);
            // change question ID
        }
    }

    free(grid.array);

    return EXIT_SUCCESS;
}
