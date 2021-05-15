#include <stdio.h>
#include <stdlib.h>

#include "../header/Display.h"
#include "../header/Dialogs.h"
#include "../header/Boats.h"
#include "../header/Grid.h"

int errorCode, answer, gameLoop, dialogID, windowID, difficulty, gameMode;
Dialog dialogArray[9];
Boat boatArray[5];
Grid grid;


void init() {
    windowID = 0;
    errorCode = 0;
    gameLoop = 1;
    dialogID = 0;

    init_display();
    init_dialogs(dialogArray);
    init_grid(&grid, 10, 10);
    init_boats(boatArray);
    place_boats(boatArray, grid);
}


void do_something(int *dialogID, int *windowID, int answer) {
    switch (*dialogID) {
        // main menu
        case 0:
            switch (answer) {
                case 1:
                    *dialogID = 1;
                    *windowID = 1;
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
        case 1:
            difficulty = answer;
            *dialogID = 2;
            *windowID = 2;
            break;

        // game mode menu
        case 2:
            gameMode = answer;
            place_boats(boatArray, grid);
            *windowID = 3;
            *dialogID = 3;
            break;

    }
}



int main() {
    init();

    while (gameLoop) {
        display_window(windowID);


        show_dialog(dialogID, errorCode, dialogArray);
        wprintf(L"Dialog %d, window %d, last answer %d\n", dialogID, windowID, answer);
        answer = get_answer();
        //wprintf(L"%d\n", answer);
        errorCode = check_answer(answer, dialogID);

        if (!errorCode) {
            do_something(&dialogID, &windowID, answer);
            //do something
            // change question ID
        } else {
            // write error message next iteration

        }
    }

    free(grid.array);

    return EXIT_SUCCESS;
}
