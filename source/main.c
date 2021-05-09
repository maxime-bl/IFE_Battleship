#include <stdio.h>
#include <stdlib.h>

#include "../header/Display.h"
#include "../header/Dialogs.h"

int errorCode=0, answer, gameLoop=1, dialogID=0;
int windowID=0; //1=Main menu, 2=Game window
Dialog dialogArray[9];


void init() {
    init_display();
    init_dialogs(dialogArray);

}


void display_window(int windowID){
    switch (windowID){
        case 0:
            show_menu();
            break;
        case 1:
            show_grid();
            break;
    }
}


int main() {
    init();

    while (gameLoop) {
        display_window(windowID);


        show_dialog(dialogID, errorCode, dialogArray);
        answer = get_answer();
        errorCode = check_answer(answer);

        scanf(" %d", answer);


    }

    return EXIT_SUCCESS;
}
