#include <stdio.h>
#include <stdlib.h>

#include "../header/Display.h"
#include "../header/Dialogs.h"
#include "../header/Grid.h"

int errorCode, answer, gameLoop, dialogID, windowID, difficulty;
Dialog dialogArray[9];
Grid grid;


void init() {
    windowID = 0;
    errorCode = 0;
    gameLoop = 1;
    dialogID = 0;

    init_display();
    init_dialogs(dialogArray);
    init_grid(&grid, 10, 10);

}


void do_something(int dialogID, int answer) {
    switch (dialogID) {
        case 0:
            // main menu
            switch (answer) {
                case 1:
                    dialogID = 1;
                    windowID = 1;
                    break;
                case 2:
                    //load the file and go to the game window
                    break;
                case 3:
                    gameLoop = 0;
                    break;
            }
            break;

        case 1:
            // difficulty menu
            difficulty = answer;
            dialogID = 2;
            windowID = 2;
            break;
    }
}



int main() {
    init();

    while (gameLoop) {
        display_window(windowID);


        show_dialog(dialogID, errorCode, dialogArray);
        answer = get_answer();
        //wprintf(L"%d\n", answer);
        errorCode = check_answer(answer, dialogID);

        if (!errorCode) {
            do_something(dialogID, answer);
            //do something
            // change question ID
        } else {
            // write error message next iteration

        }
    }

    free(grid.array);

    return EXIT_SUCCESS;
}
